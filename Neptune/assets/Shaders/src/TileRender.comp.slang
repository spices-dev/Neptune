/**
* @file TileRender.comp.slang.
* @brief This Shader Defines TileRender Compute Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#include "Header/PreRendererLayout.slangh"
#include "Header/GS3DTileRenderCommon.slangh"

/*****************************************************************************************/

/********************************Descriptor List******************************************/

/**
* @brief push constant.
*/
[[vk::push_constant]] ConstantBuffer<TileRenderPush> push;
        
[[vk::binding(0, 1)]] [[vk::image_format("rgba16f")]] RWTexture2D<float4> GS3DScene;      // @brief Render Target.

typealias Sh0Codes = float*;   // @brief Sh0Codes
        
static const float LOG2E       =  1.4426950408889634;
static const float SH_C0       = 0.28209479177387814;
static const float LOG2_1_255  = -7.994353436858858;       // log2(1 / 255)
static const float TWO_LN2     =  1.3862943611198906;      // 2 * ln(2)
static const float CULL_MARGIN =  0.05;
static const uint  NUM_WARPS   = (TILE_SIZE * TILE_SIZE) / WAVE_SIZE;

groupshared float4 sGeom[NUM_WARPS][WAVE_SIZE];
groupshared float4 sCoef[NUM_WARPS][WAVE_SIZE];
groupshared float  sSh0Codes[256];

/*****************************************************************************************/

/**********************************Functions**********************************************/
        
bool BlockHit(float2 c, float a, float b, float cc, float log2Opacity, int bx0, int by0)
{
    float det = a * cc - b * b;
    if (!(a > 0.0 && cc > 0.0 && det > 1e-12)) return true;
    
    float T      = TWO_LN2 * (log2Opacity - LOG2_1_255);
    float invDet = 1.0 / det;
    float hx     = sqrt(max(T * cc * invDet, 0.0));
    float hy     = sqrt(max(T * a  * invDet, 0.0));
    
    int xmin = int(floor(c.x - hx - 0.5 - CULL_MARGIN));
    int xmax = int(ceil (c.x + hx - 0.5 + CULL_MARGIN));
    int ymin = int(floor(c.y - hy - 0.5 - CULL_MARGIN));
    int ymax = int(ceil (c.y + hy - 0.5 + CULL_MARGIN));
    
    return (xmin <= bx0 + 7) && (xmax >= bx0) && (ymin <= by0 + 3) && (ymax >= by0);
}
        
void Blend(float4 g, float4 cf, float2 pl, inout float3 C, inout float T, inout bool done)
{
    float2 d  = pl - g.xy;
    float  pw = d.x * (g.z * d.x + g.w * d.y) + cf.x * d.y * d.y;
    float  p2 = pw + cf.y;
        
    if (done || pw > 0.0 || p2 < LOG2_1_255) return;
    
    float alpha = min(0.99, exp2(p2));
    float nT    = T * (1.0 - alpha);
    if (nT < 1e-4)
    {
        done = true;
        return;
    }
    
    uint2  cu  = asuint(cf.zw);
    float3 col = float3(UnpackHalf2x16(cu.x), UnpackHalf2x16(cu.y).x);
    C += col * (alpha * T);
    T  = nT;
}

/*****************************************************************************************/
        
/**********************************Shader Entry*******************************************/
        
[shader("compute")]
[numthreads(TILE_SIZE, TILE_SIZE, 1)]
void main(uint3 groupID : SV_GroupID, uint tid : SV_GroupIndex)
{
    uint warp = tid >> 5u;
    uint lane = tid & 31u;
    uint tile = groupID.y * push.tilesX + groupID.x;

    sSh0Codes[tid] = ((Sh0Codes)push.sh0CodesAddress)[tid];
    GroupMemoryBarrierWithGroupSync();
        
    uint2  local = uint2((warp & 1u) * 8u + (lane & 7u), (warp >> 1u) * 4u + (lane >> 3u));
    int2   pix   = int2(groupID.xy * TILE_SIZE + local);
    float2 pl    = float2(local) + 0.5;
    float2 org   = float2(groupID.xy * TILE_SIZE);
    
    int bx0 = int((warp & 1u) * 8u);
    int by0 = int((warp >> 1u) * 4u);
        
    bool inside = pix.x < int(push.width) && pix.y < int(push.height);
    bool done = !inside;

    uint rangex = ((TileRanges)push.rangeAddress)[tile * 2u + 0u];
    uint rangey = ((TileRanges)push.rangeAddress)[tile * 2u + 1u];
    uint  total = (rangey > rangex) ? (rangey - rangex) : 0u;

    TileEntries  entries = (TileEntries)push.sortedAddress;
    TileSplats   splats  = (TileSplats)push.splatAddress;
    
    float3 C = float3(0.0);
    float  T = 1.0;

    uint4    u    = uint4(0u);
    uint64_t rawN = uint64_t(0);
    
    if (total > 0u)
    {
        if (lane < total)
        {
            uint gid = uint(entries[rangex + lane]) & GID_MASK;
            u = splats[gid];
        }
        if (WAVE_SIZE + lane < total)
            rawN = entries[rangex + WAVE_SIZE + lane];
    }

    for (uint base = 0u; base < total; base += WAVE_SIZE)
    {
        if (WaveActiveAllTrue(done)) break;
        
        uint i = base + lane;

        bool   hit = false;
        float4 g   = float4(0.0);
        float4 cf  = float4(0.0);
        
        if (i < total)
        {
            float2 center0;
            float3 conic;
            float  opacity;
            UnpackSplat(u, center0, conic, opacity);

            float2 center = center0 - org;
            float  lo2    = log2(opacity);
            hit = (opacity >= 1.0 / 255.0) && BlockHit(center, conic.x, conic.y, conic.z, lo2, bx0, by0);
    
            if (hit)
            {
                uint3  ix  = UnpackSplatSh0(u);
                float3 col = float3(0.5) + float3(sSh0Codes[ix.x], sSh0Codes[ix.y], sSh0Codes[ix.z]) * SH_C0;
                g  = float4(center, -0.5 * conic.x * LOG2E, -conic.y * LOG2E);
                cf = float4(-0.5 * conic.z * LOG2E, lo2,
                            asfloat(PackHalf2x16(col.rg)),
                            asfloat(PackHalf2x16(float2(col.b, 0.0))));
            }
        }

        if (i + WAVE_SIZE < total)
        {
            uint gidN = uint(rawN) & GID_MASK;
            u = splats[gidN];
        }
        if (i + 2u * WAVE_SIZE < total)
            rawN = entries[rangex + i + 2u * WAVE_SIZE];
            
        uint hm = WaveActiveBallot(hit).x;
        if (hm != 0u)
        {
            uint pos = WavePrefixCountBits(hit);
            if (hit)
            {
                sGeom[warp][pos] = g;
                sCoef[warp][pos] = cf;
            }
            GroupMemoryBarrierWithWaveSync();

            uint n = countbits(hm);
            for (uint k = 0u; k < n; k += 2u)
            {
                float4 g0 = sGeom[warp][k];
                float4 c0 = sCoef[warp][k];
                float4 g1 = sGeom[warp][k + 1u];
                float4 c1 = sCoef[warp][k + 1u];
                
                Blend(g0, c0, pl, C, T, done);
                if (k + 1u < n) Blend(g1, c1, pl, C, T, done);
            }

            GroupMemoryBarrierWithWaveSync();
        }
    }

    if (inside)
    {
        // TODO: Blend With Depth Attachment.
        GS3DScene[uint2(pix)] = float4(C, 1.0 - T);
    }
}

/*****************************************************************************************/