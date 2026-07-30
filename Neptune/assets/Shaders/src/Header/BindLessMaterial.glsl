/**
* @file BindLessMaterial.glsl.
* @brief This Shader Header File Defines BindLess Material Structure.
* @author Spices.
*/

/************************************Pre Compile******************************************/

#ifndef BINDLESS_MATERIAL_H
#define BINDLESS_MATERIAL_H

#include "Core.h"

/*****************************************************************************************/

/****************************************Buffer Data**************************************/

/**
* @brief Buffer of all Material Parameters in World.
* Only Access index 0, unless you want access other material parameter.
*/
layout(buffer_reference, scalar, buffer_reference_align = 8) buffer MaterialParameters 
{ 
    MaterialParameter i[]; 
};
MaterialParameter materialParam;

/*****************************************************************************************/

/******************************************Functions**************************************/

/**
* @brief Explain Material Parameter to split struct and texture.
* @param[in] materialParameterAddress the MaterialParameter address.
*/
void ExplainMaterialParameter(const in uint64_t materialParameterAddress)
{
    materialParam = MaterialParameters(materialParameterAddress).i[0];
}

/*****************************************************************************************/

#endif