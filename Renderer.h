#pragma once

#include"Vector.h"
#include"Color.h"
#include"ImageView.h"
#include"DrawCommand.h"
#include"Viewport.h"
#include"Framebuffer.h"

namespace Rasterizer
{
	void Clear(ImageView<Color4UB> const& colorBuffer, const Vector4f& color);

	void Clear(const ImageView<std::uint32_t>& depthBuffer, std::uint32_t value);

    void Draw(const Framebuffer& framebuffer, 
		const Viewport& viewport,
		const DrawCommand& command);
}