/**
* @file ExtensionHeader.h.
* @brief The ExtensionHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "WaveOps.h"
#include "ExpandedComputeResourceStates.h"
#include "Int64ShaderOps.h"
#include "DepthBoundsTest.h"
#include "ProgrammableSamplePositions.h"
#include "CopyQueueTimestampQueries.h"
#include "CastingFullyTypedFormat.h"
#include "WriteBufferImmediate.h"
#include "ViewInstancing.h"
#include "Barycentrics.h"
#include "MSAA64KBAlignedTexture.h"
#include "SharedResourceCompatibility.h"
#include "Native16BitShaderOps.h"
#include "SRVOnlyTiledResource.h"
#include "Raytracing.h"
#include "AdditionalShadingRates.h"
#include "PerPrimitiveShadingRateWithViewportIndexing.h"
#include "VariableShadingRate.h"
#include "ShadingRateImageTileSize.h"
#include "BackgroundProcessing.h"

#endif