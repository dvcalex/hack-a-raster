#pragma once

#include "Mesh.h"
#include "Settings.h"

namespace Rasterizer
{
	struct DrawCommand
	{
		Mesh mesh;
		CullMode cullMode = CullMode::None;
		Types::Matrix4x4f transform = Types::Matrix4x4f::Identity();
	};
}