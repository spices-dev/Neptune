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
layout(buffer_reference, scalar, buffer_reference_align = 8) readonly buffer GS3DDescs
{
    GS3DDesc i[];             /* @see GS3DDesc. */
};
GS3DDesc desc;

/**
* @brief GS3D Model Matrix Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) readonly buffer Models
{
    mat4 i[];
};
mat4 model;

/**
* @brief MeansRanges Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) readonly buffer MeansRanges
{
    vec3 i[];
};
MeansRanges meansRanges;

/**
* @brief ScaleCodes Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 4) readonly buffer ScaleCodes
{
    float i[];
};
ScaleCodes scaleCodes;

/**
* @brief Sh0Codes Buffer.
*/
layout(buffer_reference, scalar, buffer_reference_align = 4) readonly buffer Sh0Codes
{
    float i[];
};
Sh0Codes sh0Codes;

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
    meansRanges         = MeansRanges(desc.meansRangesAddress);
    scaleCodes          = ScaleCodes(desc.scaleCodesAddress);
    sh0Codes            = Sh0Codes(desc.sh0CodesAddress);
}

/*****************************************************************************************/

#endif