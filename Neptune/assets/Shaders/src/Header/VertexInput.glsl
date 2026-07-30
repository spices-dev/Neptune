/**
* @file VertexInput.glsl.
* @brief This Shader Header File Defines Vertex Input Structure.
* @author Spices.
*/

/************************************Pre Compile******************************************/

#ifndefVERTEX_INPUT_H
#defineVERTEX_INPUT_H

/*****************************************************************************************/

/************************************Vertex Input*****************************************/

/**
* @brief Position Input from InputAssembly.
*/
layout(location = 0) in vec3 position;             /* @brief Vertex Position. */

/*****************************************************************************************/

#endif