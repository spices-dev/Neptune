/**
* @file TransparentPass.vert.
* @brief This Shader Defines TransparentPass Vertex Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#version 460

#extension GL_GOOGLE_include_directive : enable    /* @brief Enable include Macro. */

#include "Header/PreRendererLayout.glsl"
#include "Header/GS3DDescLayout.glsl"

/*****************************************************************************************/

/************************************Vertex Output****************************************/

/**
* @brief Vertex Shader Output to Fragment Shader.
*/
layout(location = 0) out struct FragInput
{
    vec2  localOffset;
    vec3  color;
    float opacity;
    vec3  conic;
}
vertOut;

/*****************************************************************************************/

/********************************Descriptor List******************************************/
        
/**
* @brief GS3DDesc Address.
*/
layout(set = 1, binding = 0) uniform UBO1 { uint64_t descAddress; };  /* @see GS3DDesc */

/**
* @brief Sort Address.
*/
layout(set = 1, binding = 1) uniform UBO2 { uint64_t sortAddress; };  /* @see Sort */
        
/**
* @brief Sort Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer Sorts
{
    uint64_t i[];             /* @biref Sort list. */
};
Sorts sorts;

/*****************************************************************************************/

mat3 QuatToMat3(vec4 q)
{
    float x = q.x, y = q.y, z = q.z, w = q.w;
        
    return 
    mat3(1.0 - 2.0*(y*y + z*z), 2.0*(x*y + w*z),       2.0*(x*z - w*y),
        2.0*(x*y - w*z),       1.0 - 2.0*(x*x + z*z), 2.0*(y*z + w*x),
        2.0*(x*z + w*y),       2.0*(y*z - w*x),       1.0 - 2.0*(x*x + y*y));
}

void EvalSHBasis(vec3 dir, out float basis[16])
{
    float x = dir.x, y = dir.y, z = dir.z;
    
    basis[0] = 0.28209479177387814;
    
    basis[1] = -0.4886025119029199 * y;
    basis[2] =  0.4886025119029199 * z;
    basis[3] = -0.4886025119029199 * x;
    
    float xx = x*x, yy = y*y, zz = z*z;
    float xy = x*y, yz = y*z, xz = x*z;
    
    basis[4] = 1.0925484305920792 * xy;
    basis[5] = -1.0925484305920792 * yz;
    basis[6] = 0.31539156525252005 * (2.0*zz - xx - yy);
    basis[7] = -1.0925484305920792 * xz;
    basis[8] = 0.5462742152960396 * (xx - yy);
    
    basis[9]  = -0.5900435899266435 * y * (3.0*xx - yy);
    basis[10] = 2.890611442640554 * xy * z;
    basis[11] = -0.4570457994644658 * y * (4.0*zz - xx - yy);
    basis[12] = 0.3731763325901154 * z * (2.0*zz - 3.0*xx - 3.0*yy);
    basis[13] = -0.4570457994644658 * x * (4.0*zz - xx - yy);
    basis[14] = 1.445305721320277 * z * (xx - yy);
    basis[15] = -0.5900435899266435 * x * (xx - 3.0*yy);
}

float GetSHCoeff(mat4 m, int idx)
{
    return m[idx / 4][idx % 4];
}

vec3 EvalSH(vec3 dir, mat4 shR, mat4 shG, mat4 shB)
{
    float basis[16];
    EvalSHBasis(dir, basis);
    
    vec3 color = vec3(0.0);
    for (int i = 0; i < 16; ++i)
    {
        color += vec3(
            GetSHCoeff(shR, i),
            GetSHCoeff(shG, i),
            GetSHCoeff(shB, i)
        ) * basis[i];
    }
    
    color += 0.5;
    return max(color, vec3(0.0));
}
        
/**********************************Shader Entry*******************************************/

void main()
{
    ExplainGS3DDesciption(descAddress);

    sorts = Sorts(sortAddress);

    uint64_t entry = sorts.i[gl_InstanceIndex];
    uint gID = uint(entry & 0xFFFFFFFFu);
    uint cID = gl_VertexIndex;

    if (gID >= 500000)
    {
        return;
    }
        
    model = mat4(1.0, 0.0,   0.0,   0.0,
                0.0,   1.0, 0.0,   0.0,
                0.0,   0.0,   1.0, 0.0,
                0.0,   0.0,   0.0,   1.0);
            
    vec3  worldPos  = (model * vec4(positions.i[gID], 1.0)).xyz;
    vec3  scale     = scales.i[gID];
    vec4  quat      = orientations.i[gID];
    float opacity   = alphas.i[gID];
    vec3  baseColor = colors.i[gID];

    vec4 viewPos = view.view * vec4(worldPos, 1.0);
    vec4 clipPos = view.projection * viewPos;

    if (viewPos.z >= -0.2)
    {
        gl_Position = vec4(0.0, 0.0, 2.0, 1.0);
            
        //return;
    }

    mat3 R = QuatToMat3(quat);
    mat3 S = mat3(scale.x, 0.0, 0.0,
                  0.0, scale.y, 0.0,
                  0.0, 0.0, scale.z);
    mat3 Sigma = R * S * S * transpose(R);

    mat3 W = mat3(view.view);
    float focalX = view.projection[0][0] * (view.sceneTextureSize.x  * 0.5);
    float focalY = view.projection[1][1] * (view.sceneTextureSize.y * 0.5);

    float invZ  = 1.0 / viewPos.z;
    float invZ2 = invZ * invZ;
    mat3 J = mat3(focalX * invZ, 0.0,           -focalX * viewPos.x * invZ2,
                  0.0,           focalY * invZ, -focalY * viewPos.y * invZ2,
                  0.0,           0.0,            0.0);
    
    mat3 T   = J * W;
    mat3 cov = T * Sigma * transpose(T);

    cov[0][0] += 0.3;
    cov[1][1] += 0.3;
    
    float a = cov[0][0];
    float b = cov[0][1];
    float c = cov[1][1];

    float det = a * c - b * b;
    if (det <= 0.0)
    {
        gl_Position = vec4(0.0, 0.0, 2.0, 1.0);
        //return;
    }
    
    float mid     = 0.5 * (a + c);
    float lambda1 = mid + sqrt(max(0.1, mid * mid - det));
    float lambda2 = mid - sqrt(max(0.1, mid * mid - det));
    float radius  = ceil(3.0 * sqrt(max(lambda1, lambda2)));

    float invDet = 1.0 / det;
    vec3 conic = vec3(c * invDet, -b * invDet, a * invDet);

    const vec2 corners[4] = vec2[](vec2(-1,-1), vec2(1,-1), vec2(-1,1), vec2(1,1));
    vec2 corner       = corners[cID];
    vec2 screenOffset = corner * radius;

    vec2 ndcOffset = screenOffset / vec2(view.sceneTextureSize.x, view.sceneTextureSize.y) * 2.0;
    
    gl_Position    = clipPos;
    gl_Position.xy += ndcOffset * clipPos.w;

    vec3 camPos = view.inView[3].xyz;
    vec3 dir = normalize(worldPos - camPos);
    
    vec3 shColor = EvalSH(dir, sphrs.i[gID], sphgs.i[gID], sphbs.i[gID]);
        
    vertOut.localOffset = screenOffset;
    vertOut.color       = shColor;
    vertOut.opacity     = opacity;
    vertOut.conic       = conic;
}

/*****************************************************************************************/