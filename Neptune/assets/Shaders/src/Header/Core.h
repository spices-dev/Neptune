/**
* @file Core.h.
* @brief This Shader Core Header File Defines Shader Structure both Shader side and C++ side.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#ifndef CORE_H
#define CORE_H

#ifdef __cplusplus
#include <cstdint>
#include <glm/glm.hpp>

namespace Neptune::ShaderCore
{
using float2   = glm::vec2;     
using float3   = glm::vec3;     
using float4   = glm::vec4;     
using uint2    = glm::uvec2;     
using uint3    = glm::uvec3;     
using uint4    = glm::uvec4;     
using float4x4 = glm::mat4;     
using uint     = unsigned int; 

#endif

/**
* @brief Macros.
*/
#define VIEWPORT_FLIP_Y                                                          /* @brief ViewPort Flip Y                                       */
	
/**
* @brief Macros for Variable Constant.
*/
static const uint BINDLESS_TEXTURE_MAXNUM        = 65535                     ;   /* @brief Maximum number of BindLess Texture Array.             */
static const uint BINDLESS_TEXTURE_SET           = 1                         ;   /* @brief BindLess Texture Descriptor Set.                      */
static const uint BINDLESS_TEXTURE_BINDING       = 0                         ;   /* @brief BindLess Texture Descriptor Set Binding.              */
static const uint MESH_BUFFER_MAXNUM             = 100000                    ;   /* @brief Ray Tracing Renderer Maximum mesh desc buffer count.  */
static const uint DIRECTIONALLIGHT_BUFFER_MAXNUM = 100                       ;   /* @brief Maximum number of Directional lights.                 */
static const uint POINTLIGHT_BUFFER_MAXNUM       = 10000                     ;   /* @brief Maximum number of Point lights.                       */
static const uint MESHLET_NVERTICES              = 64                        ;   /* @brief Maximum number of Meshlet's nVertices.                */
static const uint MESHLET_NPRIMITIVES            = 124                       ;   /* @brief Maximum number of Meshlet's nPrimitives.              */
          
static const uint NV_SUBGROUP_SIZE               = 32                        ;   /* @brief Nvidia Hardware only support 32 subgroup size.        */
static const uint AMD_SUBGROUP_SIZE              = 64                        ;   /* @brief AMD    Hardware only support 64 subgroup size.        */
          
static const uint SUBGROUP_SIZE                  = NV_SUBGROUP_SIZE          ;   /* @brief Use Nvidia Hardware.                                  */

static const uint POST_BLOOM_MIPMAP              = 5                         ;   /* @brief PostRenderer Bloom mipmap count.                      */

/**
* @brief  Macros for Calculate Constant.
*/
static const float2 invAtan                       = float2(0.1591, 0.3183)    ;     /* @brief inverse arctan.                                       */
static const float  PI                            = 3.141592654f              ;     /* @brief PI.                                                   */
static const float  BIAS                          = 0.01f                     ;     /* @brief small blas.                                           */
static const float  EPS                           = 1e-6f                     ;     /* @brief small eps.                                            */

/*****************************************************************************************/


/***************************************Vertex********************************************/

/**
* @brief This Struct defines Per Vertex Struct of Mesh.
*/
struct Vertex
{
	float3 position;            /* @brief Vertex Position in local world. */
	float3 normal;              /* @brief Vertex Normal.                  */
	float3 color;               /* @brief Vertex Color.                   */
	float2 texCoord;            /* @brief Vertex UV.                      */
};

/**
* @brief This Struct defines Per Half Edge Struct of Mesh.
*/
struct HalfEdge
{
	uint first;               /* @brief Half Edge first Vertex index.        */
	uint second;              /* @brief Half Edge second Vertex index.       */
};

/**
* @brief Using Pixel rather than Vertex in shader mey be easier to understand.
* It defines pixel data, not be original vertex data.
*/
#define Pixel Vertex

/**
* @brief GBuffer Data per pixel, for SceneCompose Renderer Fragment Shader use.
*/
struct GBufferPixel
{
	float3 albedo;              /* @brief Albedo.     */
	float3 normal;              /* @brief Normal.     */
	float  roughness;           /* @brief Roughness.  */
	float  metallic;            /* @brief Metallic.   */
	float3 position;            /* @brief Position.   */
};

/*****************************************************************************************/


/**************************************Material*******************************************/

/**
* @brief This Struct defines PBR Material Attribute.
*/
struct MaterialAttributes
{
	float3 albedo;              /* @brief Albedo, used for Reflection attenuation.                       */
	float  roughness;           /* @brief Roughness, used for Reflection direction.                      */
	float  metallic;            /* @brief Metallic, used for                                             */
	float3 emissive;            /* @brief Emissive, used for Direct illumination.                        */
	float3 normal;              /* @brief Normal, used for light effect.                                 */
	uint   maxRayDepth;         /* @brief Max Ray Tracing Depth, defined specific from material.         */
	uint   maxLightDepth;       /* @brief Max Ray Tracing Light Depth, defined specific from material.   */
	uint   maxShadowDepth;      /* @brief Max Ray Tracing Shadow Depth, defined specific from material.  */
};

/*****************************************************************************************/


/*************************************Pre Renderer Data***********************************/

/**
* @brief Global View Struct.
*/
struct View 
{
	float4x4 projection;          /* @brief Projection Matrix from major Camera Entity.                   */
	float4x4 inProjection;        /* @brief Inverse Projection Matrix from major Camera Entity.           */
	float4x4 nprojection;         /* @brief Negative y-axis Projection Matrix from major Camera Entity.   */
	float4x4 view;                /* @brief View Matrix from major Camera Entity.                         */
	float4x4 inView;              /* @brief Inverse View Matrix from major Camera Entity.                 */
	float4   sceneTextureSize;    /* @brief Scene Texture Size.                                           */
	float4   windowSize;          /* @brief Application Window Size.                                      */
	uint     stableFrames;        /* @brief Camera Stable Frames Number.                                  */
	float    fov;                 /* @brief Camera Radians fov.                                           */
};

/**
* @brief Application Inout Struct.
*/
struct Input
{
	float4 mousePos;            /* @brief Mouse Position and inverse position. */
	float  engineTime;          /* @brief Application Run time since start.    */
	float  frameTime;           /* @brief Duration time since last frame.      */
};

/*****************************************************************************************/


/******************************************Light Data*************************************/

/**
* @brief This struct defines DirectionalLight data.
*/
struct DirectionalLight
{
	float4x4 rotationMatrix;      /* @brief Rotation of SunLight.   */
	float3   color;               /* @brief Color of SunLight.      */
	float    intensity;           /* @brief Intensity of SunLight.  */
};

/**
* @brief This struct defines PointLight data.
*/
struct PointLight
{
	float3 position;            /* @brief World Position of PointLight. */
	float3 color;               /* @brief Color of PointLight.          */
	float  intensity;           /* @brief Intensity of PointLight.      */
	float  constantf;           /* @brief Constantf of PointLight.      */
	float  linear;              /* @brief Linear of PointLight.         */
	float  quadratic;           /* @brief Quadratic of PointLight.      */
};

/*****************************************************************************************/


/***********************************SOP Description Data**********************************/

/**
* @brief Polygon Description Struct.
*/
struct PolygonDesc
{
	uint64_t modelAddress;                    /* @brief Address of the Model Matrix.                      */
	uint64_t positionsAddress;                /* @brief Address of the Positions buffer.                  */
	uint64_t normalsAddress;                  /* @brief Address of the Normals buffer.                    */
	uint64_t colorsAddress;                   /* @brief Address of the Colors buffer.                     */
	uint64_t texCoordsAddress;                /* @brief Address of the TexCoords buffer.                  */
	uint64_t verticesAddress;                 /* @brief Address of the Vertices buffer.                   */
	uint64_t primitivePointsAddress;          /* @brief Address of the PrimitivePoints buffer.            */
	uint64_t primitiveVerticesAddress;        /* @brief Address of the PrimitiveVertices buffer.          */
	uint64_t primitiveLocationsAddress;       /* @brief Address of the PrimitiveLocationsAddress buffer.  */
	uint64_t meshletsAddress;                 /* @brief Address of the Meshlet Buffer.                    */
	uint64_t materialParameterAddress;        /* @brief Address of the Material Parameter buffer.         */
	uint64_t nMeshlets;                       /* @brief Meshlets Count.                                   */
	uint64_t entityID;                        /* @brief EntityId, cast from entt::entity.                 */
};

/*****************************************************************************************/


/*********************************RayTracing Renderer Data********************************/

/**
* @brief Ray Tracing Shader Data Location 0. 
*/
struct HitPayLoad
{
	float3 hitValue;                  /* @brief Current Hit Fragment Color.                                                */
	uint   seed;                      /* @brief Random Seed for BRDF Lambertian Light Reflection Direction Select.         */
	uint   rayDepth;                  /* @brief Ray Tracing Depth for diffuse.                                             */
	float3 rayOrigin;                 /* @brief Next Ray Original World Position.                                          */
	float3 rayDirection;              /* @brief Next Ray Direction in World Space.                                         */
	float3 weight;                    /* @brief Current Fragment Color Weight.                                             */
	uint   maxRayDepth;               /* @brief Max Ray Tracing Depth, defined specific from material.                     */
	uint   entityID;                  /* @brief Entity ID from Closest Hit to Ray Gen Shader to RayEntityID Image.         */
	uint   triangleID;                /* @brief Triangle ID from Closest Hit to Ray Gen Shader to RayTriangleID Image.     */
	float  depth;                     /* @brief Hit point depth to camera.                                                 */
};

/*****************************************************************************************/


/*********************************************Mesh***************************************/

/**
* @brief Sphere Struct.
*/
struct Sphere
{
	float3 c;                                          /* @brief Center of Bound Sphere.                 */
	float  r;                                          /* @brief Radius of Bound Sphere.                 */
};

/**
* @brief Bound AABB Struct.
*/
struct AABB
{
	float3 min;                                         /* @brief Min of Bound AABB.                 */    
	float3 max;                                         /* @brief Max of Bound AABB.                 */
};

/**
* @brief Meshlet Structure Data.
*/
struct Meshlet
{
	uint   vertexOffset;                        /* @brief Offset of Vertices this meshlet.        */
	uint   primitiveOffset;                     /* @brief Offset of primitives this meshlet.      */
	uint   nVertices;                           /* @brief Vertices Count this meshlet.( <= 64)    */
	uint   nPrimitives;                         /* @brief Primitives Count this meshlet.( <= 126) */
	uint   lod;                                 /* @brief Current meshlet lod level.              */
	Sphere boundSphere;                         /* @brief Bounding Sphere in local world.         */
	Sphere clusterBoundSphere;                  /* @brief Cluster Bounding Sphere in local world. */
	float3 coneApex;                            /* @brief Normal Cone center.                     */
	float3 coneAxis;                            /* @brief Normal Cone axis.                       */
	float  coneCutoff;                          /* @brief Normal Cone cutoff rate.                */
};

/*****************************************************************************************/

#ifdef __cplusplus
}
#else
	
/**********************************Functions**********************************************/
	
/**
* @brief GLSL style mod.
* 
* @param[in] x .
* @param[in] y .
* 
* @return Returns mod value.
*/
float Mod(float x, float y)
{
	return x - y * floor(x / y);
}
	
/*****************************************************************************************/

#endif

#endif