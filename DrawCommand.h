#pragma once

#include "Mesh.h"
#include "Settings.h"
#include "Matrix.h"

namespace Rasterizer
{
	struct DrawCommand
	{
		Mesh mesh;
		CullMode cullMode = CullMode::None;
		Matrix4x4f transform = Matrix4x4f::Identity();
	};
}