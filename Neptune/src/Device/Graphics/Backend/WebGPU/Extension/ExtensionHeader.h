/**
* @file ExtensionHeader.h.
* @brief The ExtensionHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "TimedWaitAny.h"
#include "ShaderSourceSPIRV.h"
#include "MultipleDevicesPerAdapter.h"
#include "ReadonlyAndReadwriteStorageTextures.h"
#include "Packed4x8IntegerDotProduct.h"
#include "UnrestrictedPointerParameters.h"
#include "PointerCompositeAccess.h"
#include "CoreFeaturesAndLimits.h"
#include "DepthClipControl.h"
#include "Depth32FloatStencil8.h"
#include "TextureCompressionBC.h"
#include "TextureCompressionBCSliced3D.h"
#include "TextureCompressionETC2.h"
#include "TextureCompressionASTC.h"
#include "TextureCompressionASTCSliced3D.h"
#include "TimestampQuery.h"
#include "IndirectFirstInstance.h"
#include "ShaderF16.h"
#include "RG11B10UfloatRenderable.h"
#include "BGRA8UnormStorage.h"
#include "Float32Filterable.h"
#include "Float32Blendable.h"
#include "ClipDistances.h"
#include "DualSourceBlending.h"
#include "Subgroups.h"
#include "TextureFormatsTier1.h"
#include "TextureFormatsTier2.h"
#include "PrimitiveIndex.h"
#include "Unorm16TextureFormats.h"
#include "Snorm16TextureFormats.h"
#include "MultiDrawIndirect.h"

#endif