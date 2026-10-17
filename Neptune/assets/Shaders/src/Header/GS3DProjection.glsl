/**
* @file GS3DProjection.glsl.
* @brief This Shader Header File Defines GS3DProjection Functions.
* @author Spices.
*/

/************************************Pre Compile*******************************************/
        
#ifndef GS3D_PROJECTION_H
#define GS3D_PROJECTION_H

#include "Core.h"

/*****************************************************************************************/

/**************************************Constant*******************************************/

const float kGSMaxRadiusRatio = 0.35f;

/*****************************************************************************************/

/******************************************Functions**************************************/

/**
* @brief Transform Quaterion to Matrix.
*
* @param[in] q Quaterion.
*
* @return Returns Matrix.
*/
mat3 QuatToMat3(vec4 q)
{
    float x = q.x, y = q.y, z = q.z, w = q.w;

    return
    mat3(1.0 - 2.0*(y*y + z*z), 2.0*(x*y + w*z),       2.0*(x*z - w*y),
         2.0*(x*y - w*z),       1.0 - 2.0*(x*x + z*z), 2.0*(y*z + w*x),
         2.0*(x*z + w*y),       2.0*(y*z - w*x),       1.0 - 2.0*(x*x + y*y));
}

/**
* @brief Calculate Gassian Project.
* 
* @param[in] p Position.
* @param[in] s Scale.
* @param[in] q Quaterion.
* @param[out] clipPos .
* @param[out] viewPos .
* @param[out] conic .
* @param[out] majorAxis .
* @param[out] r1 .
* @param[out] minorAxis .
* @param[out] r2 .
* @param[out] radius .
*
* @return Returns true if visible.
*/
bool ProjectGaussian(vec3 p, vec3 s, vec4 q,
    out vec4 clipPos, out vec4 viewPos, out vec3 conic, 
    out vec2 majorAxis, out float r1,
    out vec2 minorAxis, out float r2, 
    out float radius
){
    viewPos = view.view * vec4(p, 1.0);
    clipPos = view.projection * viewPos;

    conic     = vec3(0.0); 
    majorAxis = vec2(1,0); 
    minorAxis = vec2(0,1);
    
    r1     = 0.0; 
    r2     = 0.0; 
    radius = 0.0;

    if (viewPos.z <= 0.01) return false;

    mat3 R     = QuatToMat3(q);
    mat3 S     = mat3(s.x,0,0, 0,s.y,0, 0,0,s.z);
    mat3 Sigma = R * S * S * transpose(R);

    mat3 W       = mat3(view.view);
    float focalX = view.projection[0][0] * (view.sceneTextureSize.x * 0.5);
    float focalY = view.projection[1][1] * (view.sceneTextureSize.y * 0.5);

    float invZ  = 1.0 / viewPos.z;
    float invZ2 = invZ * invZ;
    mat3 J = mat3(focalX * invZ              , 0.0                        , 0.0,
                  0.0                        , focalY * invZ              , 0.0,
                  -focalX * viewPos.x * invZ2, -focalY * viewPos.y * invZ2, 0.0);

    mat3 T   = J * W;
    mat3 cov = T * Sigma * transpose(T);
    
    cov[0][0] += 0.3; 
    cov[1][1] += 0.3;

    float a = cov[0][0];
    float b = cov[0][1];
    float c = cov[1][1];
    
    float det = a * c - b * b;
    if (det <= 0.0) return false;

    float mid     = 0.5 * (a + c);
    float lambda1 = mid + sqrt(max(0.1, mid * mid - det));
    float lambda2 = mid - sqrt(max(0.1, mid * mid - det));
    radius        = ceil(3.0 * sqrt(max(lambda1, lambda2)));
    
    float maxRadius = kGSMaxRadiusRatio * min(view.sceneTextureSize.x, view.sceneTextureSize.y);
    if (!(radius > 0.0 && radius <= maxRadius)) return false;
    
    vec2 ndc  = clipPos.xy / clipPos.w;
    vec2 pix  = (ndc * 0.5 + 0.5) * view.sceneTextureSize.xy;
    if (pix.x < -radius || pix.x > view.sceneTextureSize.x + radius ||
        pix.y < -radius || pix.y > view.sceneTextureSize.y + radius) return false;

    float invDet   = 1.0 / det;
    conic          = vec3(c * invDet, -b * invDet, a * invDet);

    float disc     = sqrt(max(mid * mid - det, 0.0));
    float lambdaT  = mid + disc;
    vec2  ev       = (a >= c) ? vec2(lambdaT - c, b) : vec2(b, lambdaT - a);
    float evLen2   = dot(ev, ev);
    majorAxis      = (evLen2 > 1e-20) ? ev * inversesqrt(evLen2) : vec2(1.0, 0.0);
    minorAxis      = vec2(-majorAxis.y, majorAxis.x);

    r1             = max(3.0 * sqrt(max(lambda1, 0.0)), 1.0);
    r2             = max(3.0 * sqrt(max(lambda2, 0.0)), 1.0);

    return true;
}

/*****************************************************************************************/

#endif