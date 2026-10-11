/**
* @file GS3DDescLayout.glsl.
* @brief This Shader Header File Defines GS3D Descriptions.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#ifndef GS3D_DESC_LAYOUT_H
#define GS3D_DESC_LAYOUT_H

#include "GS3DTileRenderCore.h"

/*****************************************************************************************/

/****************************************Buffer Data**************************************/

/**
* @brief GS3D Desciption Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer GS3DDescs
{
    GS3DDesc i[];             /* @see GS3DDesc. */
};
GS3DDesc desc;

/**
* @brief GS3D Model Matrix Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer Models
{
    mat4 i[];
};
mat4 model;

/**
* @brief Positions Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer Positions
{
    vec3 i[];
};
Positions positions;

/**
* @brief Colors Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer Colors
{
    vec3 i[];
};
Colors colors;

/**
* @brief Alphas Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer Alphas
{
    float i[];
};
Alphas alphas;

/**
* @brief Scales Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer Scales
{
    vec3 i[];
};
Scales scales;

/**
* @brief Orientations Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer Orientations
{
    vec4 i[];
};
Orientations orientations;

/**
* @brief SPH_Rs Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer SPH_Rs
{
    mat4 i[];
};
SPH_Rs sphrs;

/**
* @brief SPH_Gs Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer SPH_Gs
{
    mat4 i[];
};
SPH_Gs sphgs;

/**
* @brief SPH_Bs Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer SPH_Bs
{
    mat4 i[];
};
SPH_Bs sphbs;

/**
* @brief Normals Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer Normals
{
    vec3 i[];
};
Normals normals;

/**
* @brief Albedos Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer Albedos
{
    vec3 i[];
};
Albedos albedos;

/*****************************************************************************************/

/******************************************Functions**************************************/

/**
* @brief Explain GS3D Desciption to split variable.
* 
* @param[in] gs3dDescAddress The GS3D Desciption Buffer Address address.
*/
void ExplainGS3DDesciption(const in uint64_t gs3dDescAddress)
{
    desc                = GS3DDescs(gs3dDescAddress).i[0];
    model               = Models(desc.modelAddress).i[0];
    positions           = Positions(desc.positionsAddress);
    colors              = Colors(desc.colorsAddress);
    alphas              = Alphas(desc.alphasAddress);
    scales              = Scales(desc.scalesAddress);
    orientations        = Orientations(desc.orientationsAddress);
    sphrs               = SPH_Rs(desc.sphrsAddress);
    sphgs               = SPH_Gs(desc.sphgsAddress);
    sphbs               = SPH_Bs(desc.sphbsAddress);
    normals             = Normals(desc.normalsAddress);
    albedos             = Albedos(desc.albedosAddress);
}

/*****************************************************************************************/

#endif