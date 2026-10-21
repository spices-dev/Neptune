/**
* @file TileRenderPreprocess.comp.slang.
* @brief This Shader Defines TileRenderPreprocess Compute Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#include "Header/PreRendererLayout.slangh"
#include "Header/GS3DDescLayout.slangh"
#include "Header/GS3DProjection.slangh"
#include "Header/GS3DTileRenderCommon.slangh"

/*****************************************************************************************/

/********************************Descriptor List******************************************/

[[vk::binding(0, 1)]] Sampler2D<uint4> means0Image;
[[vk::binding(1, 1)]] Sampler2D<uint4> means1Image;
[[vk::binding(2, 1)]] Sampler2D<uint4> scalesImage;
[[vk::binding(3, 1)]] Sampler2D<uint4> quatsImage;
[[vk::binding(4, 1)]] Sampler2D<uint4> sh0Image;

/**
* @brief push constant.
*/
[[vk::push_constant]] ConstantBuffer<PreProcessPush> push;

static const float INV_SQRT2 = 0.7071067811865476;
        
/*****************************************************************************************/

/******************************************Functions**************************************/

bool TileOverlaps(int2 t, float2 c, float2 a1, float r1, float2 a2, float r2)
{
    float2 d  = (float2(t) + 0.5) * float(TILE_SIZE) - c;
    float  h  = 0.5 * float(TILE_SIZE);
    if (abs(dot(d, a1)) > r1 + h * (abs(a1.x) + abs(a1.y))) return false;
    if (abs(dot(d, a2)) > r2 + h * (abs(a2.x) + abs(a2.y))) return false;
    return true;
}

float4 unpackSmallestThree(uint r, uint g, uint b, uint a)
{
    int maxComp = int(a) - 252;

    float v0 = (float(r) / 255.0 * 2.0 - 1.0) * INV_SQRT2;
    float v1 = (float(g) / 255.0 * 2.0 - 1.0) * INV_SQRT2;
    float v2 = (float(b) / 255.0 * 2.0 - 1.0) * INV_SQRT2;
        
    float sumSq = v0*v0 + v1*v1 + v2*v2;
    float omitted = sqrt(max(0.0, 1.0 - sumSq));
    
    float4 q = float4(0.0);
    switch (maxComp) 
    {
        case 0: q = float4(v0, v1, v2, omitted); break;
        case 1: q = float4(omitted, v1, v2, v0); break;
        case 2: q = float4(v1, omitted, v2, v0); break;
        case 3: q = float4(v1, v2, omitted, v0); break;
        default: q = float4(0.0, 0.0, 0.0, 1.0); break;
    }
    return q;
}

/*****************************************************************************************/

/**********************************Shader Entry*******************************************/
        
[shader("compute")]
[numthreads(256, 1, 1)]
void main(uint3 dispatchID : SV_DispatchThreadID)
{
    ExplainGS3DDesciption(push.descAddress);

    uint gid    = dispatchID.x;
    bool alive  = gid < push.gsCount;
    int2 texel  = int2(int(gid % push.imageWidth), int(gid / push.imageWidth));

    uint4 l       = uint4(0u);
    uint4 h       = uint4(0u);
    uint4 idx     = uint4(0u);
    uint4 qRaw    = uint4(0u, 0u, 0u, 255u);
    uint4 sh0Raw  = uint4(0u);

     if (alive)
    {
        l      = means0Image.Load(int3(texel, 0));
        h      = means1Image.Load(int3(texel, 0));
        idx    = scalesImage.Load(int3(texel, 0));
        qRaw   = quatsImage.Load(int3(texel, 0));
        sh0Raw = sh0Image.Load(int3(texel, 0));
    }

    float3 mrMin = meansRanges[0];
    float3 mrMax = meansRanges[1];

    float  opacity = 0.0;
    float3 pos     = float3(0.0);
    float3 scale   = float3(1.0);
    float4 quat    = float4(0.0, 0.0, 0.0, 1.0);
    
    if (alive)
    {
        uint qx = (h.r << 8u) | l.r;
        uint qy = (h.g << 8u) | l.g;
        uint qz = (h.b << 8u) | l.b;
        
        float3 n  = mrMin + (mrMax - mrMin) * (float3(float(qx), float(qy), float(qz)) / 65535.0);
        pos       = sign(n) * (exp(abs(n)) - 1.0);
        
        scale     = exp(float3(scaleCodes[idx.r], scaleCodes[idx.g], scaleCodes[idx.b]));
        quat      = unpackSmallestThree(qRaw.r, qRaw.g, qRaw.b, qRaw.a);
        
        opacity   = float(sh0Raw.a) / 255.0;
        alive     = opacity >= 1.0 / 255.0;
    }
        
    uint   count  = 0u;
    bool   single = false;
    uint   ovLo   = 0u;
    uint   ovHi   = 0u;
    uint   tiles  = 0u;
    int2   tMin   = int2(0), tMax = int2(-1);
    float2 center = float2(0.0), majorAxis = float2(0.0), minorAxis = float2(0.0);
    float3 conic  = float3(0.0);
    float4 viewPos = float4(0.0);
    float  r1 = 0.0, r2 = 0.0;

     if (alive)
    {
        model = float4x4(1.0,0,0,0, 0,1.0,0,0, 0,0,1.0,0, 0,0,0,1.0);
        float3 worldPos = mul(model, float4(pos, 1.0)).xyz;
        
        float4 clipPos; float radius;
        if (ProjectGaussian(worldPos, scale, quat,
            clipPos, viewPos, conic,
            majorAxis, r1,
            minorAxis, r2,
            radius))
        {
            float2 size = float2(view.sceneTextureSize.x, view.sceneTextureSize.y);
            center      = (clipPos.xy / clipPos.w * 0.5 + 0.5) * size;
#ifdef VIEWPORT_FLIP_Y
            center.y     = size.y - center.y;
            majorAxis.y  = -majorAxis.y;
            minorAxis.y  = -minorAxis.y;
            conic.y      = -conic.y;
#endif

            float k = min(1.0, sqrt(2.0 * log(255.0 * opacity)) / RADIUS_SIGMA);
            r1 *= k;  r2 *= k;
            
            float2 halfExt = abs(r1 * majorAxis) + abs(r2 * minorAxis);
            int2   rawMin  = int2(floor((center - halfExt) / float(TILE_SIZE)));
            int2   rawMax  = int2(floor((center + halfExt) / float(TILE_SIZE)));
            
            if (!(rawMax.x < 0 || rawMax.y < 0 || rawMin.x >= int(push.tilesX) || rawMin.y >= int(push.tilesY)))
            {
                tMin   = max(rawMin, int2(0));
                tMax   = min(rawMax, int2(int(push.tilesX) - 1, int(push.tilesY) - 1));
                tiles  = uint((tMax.x - tMin.x + 1) * (tMax.y - tMin.y + 1));
                single = all(rawMin == rawMax);
                
                if (single)
                {
                    count = 1u;
                }
                else if (tiles <= 64u)
                {
                    uint i = 0u;
                    for (int ty = tMin.y; ty <= tMax.y; ++ty)
                        for (int tx = tMin.x; tx <= tMax.x; ++tx, ++i)
                            if (TileOverlaps(int2(tx, ty), center, majorAxis, r1, minorAxis, r2))
                            {
                                uint bit = 1u << (i & 31u);
                                if (i < 32u) ovLo |= bit; else ovHi |= bit; 
                            }
                    count = countbits(ovLo) + countbits(ovHi);
                }
                else
                {
                    for (int ty = tMin.y; ty <= tMax.y; ++ty)
                        for (int tx = tMin.x; tx <= tMax.x; ++tx)
                            if (TileOverlaps(int2(tx, ty), center, majorAxis, r1, minorAxis, r2)) ++count;
                }
            }
        }
    }
    
    uint prefix   = WavePrefixSum(count);
    uint total    = WaveActiveSum(count);
    uint warpBase = 0u;
    if (WaveIsFirstLane() && total > 0u)
    {
        TileSortInfos infos = (TileSortInfos)push.infoAddress;
        InterlockedAdd(infos[0].instanceCounter, total, warpBase);
    }

    if (count > 0u)
    {
        TileSplats sv = (TileSplats)push.splatAddress;
        sv[gid] = PackSplat(center, conic, sh0Raw);
    }

    warpBase = WaveReadLaneFirst(warpBase);
    
    if (count == 0u) return;
    
    uint base = warpBase + prefix;
    if (base >= MAXTILEGAUSSIANS) return;
    uint limit = min(count, MAXTILEGAUSSIANS - base);

    TileEntries entries = (TileEntries)push.entryAddress;
    uint n = 0u;
    
    if (single)
    {
        entries[base] = MakeSortKey(uint(tMin.y) * push.tilesX + uint(tMin.x), viewPos.z, gid);
        n = 1u;
    }
    else if (tiles <= 64u)
    {
        uint  w    = uint(tMax.x - tMin.x + 1);
        float invW = 1.0 / float(w);
        for (uint hw = 0u; hw < 2u; ++hw)
        {
            uint m = (hw == 0u) ? ovLo : ovHi;
            while (m != 0u && n < limit)
            {
                uint bit = uint(firstbitlow(m));
                m &= m - 1u;
            
                uint tIdx = bit + hw * 32u;
                uint row  = uint((float(tIdx) + 0.5) * invW);
                uint col  = tIdx - row * w;
                uint ty   = uint(tMin.y) + row;
                uint tx   = uint(tMin.x) + col;
                entries[base + n] = MakeSortKey(ty * push.tilesX + tx, viewPos.z, gid);
                n++;
            }
        }
    }
    else
    {
        for (int ty = tMin.y; ty <= tMax.y; ++ty)
            for (int tx = tMin.x; tx <= tMax.x; ++tx)
                if (n < limit && TileOverlaps(int2(tx, ty), center, majorAxis, r1, minorAxis, r2))
                {
                    entries[base + n] = MakeSortKey(uint(ty) * push.tilesX + uint(tx), viewPos.z, gid);
                    n++;
                }
    }
        
    for (; n < limit; ++n) entries[base + n] = ~uint64_t(0);
}

/*****************************************************************************************/