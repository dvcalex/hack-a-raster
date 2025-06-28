// this file was made by Gemini

#include"Pyramid.h" // Assuming this header defines Vector3f, Vector4f, and Mesh

#include <cstdint>

namespace Rasterizer
{
	// Array of vertex positions for the pyramid
	// Each set of 3 (for triangular faces) or 4 (for base) defines a face's vertices
	static Vector3f pyramidPositions[] =
	{
		// Front Face (Triangle: FL, FR, Apex) - Red
		{-1.f, 0.f, 1.f},  // V0: Front-Left base
		{ 1.f, 0.f, 1.f},  // V1: Front-Right base
		{ 0.f, 2.f, 0.f},  // V2: Apex

		// Right Face (Triangle: FR, BR, Apex) - Green
		{ 1.f, 0.f, 1.f},  // V3: Front-Right base (same as V1)
		{ 1.f, 0.f, -1.f}, // V4: Back-Right base
		{ 0.f, 2.f, 0.f},  // V5: Apex (same as V2)

		// Back Face (Triangle: BR, BL, Apex) - Blue
		{ 1.f, 0.f, -1.f}, // V6: Back-Right base (same as V4)
		{-1.f, 0.f, -1.f}, // V7: Back-Left base
		{ 0.f, 2.f, 0.f},  // V8: Apex (same as V2)

		// Left Face (Triangle: BL, FL, Apex) - Yellow
		{-1.f, 0.f, -1.f}, // V9: Back-Left base (same as V7)
		{-1.f, 0.f, 1.f},  // V10: Front-Left base (same as V0)
		{ 0.f, 2.f, 0.f},  // V11: Apex (same as V2)

		// Base Face (Square: BL, BR, FR, FL, two triangles) - Cyan
		{-1.f, 0.f, -1.f}, // V12: Back-Left base (unique for base face)
		{ 1.f, 0.f, -1.f}, // V13: Back-Right base (unique for base face)
		{ 1.f, 0.f, 1.f},  // V14: Front-Right base (unique for base face)
		{-1.f, 0.f, 1.f},  // V15: Front-Left base (unique for base face)
	};

	// Array of colors corresponding to each vertex position
	static Vector4f pyramidColors[] =
	{
		// Front Face (Red)
		{1.f, 0.f, 0.f, 1.f},
		{1.f, 0.f, 0.f, 1.f},
		{1.f, 0.f, 0.f, 1.f},

		// Right Face (Green)
		{0.f, 1.f, 0.f, 1.f},
		{0.f, 1.f, 0.f, 1.f},
		{0.f, 1.f, 0.f, 1.f},

		// Back Face (Blue)
		{0.f, 0.f, 1.f, 1.f},
		{0.f, 0.f, 1.f, 1.f},
		{0.f, 0.f, 1.f, 1.f},

		// Left Face (Yellow)
		{1.f, 1.f, 0.f, 1.f},
		{1.f, 1.f, 0.f, 1.f},
		{1.f, 1.f, 0.f, 1.f},

		// Base Face (Cyan)
		{0.f, 1.f, 1.f, 1.f},
		{0.f, 1.f, 1.f, 1.f},
		{0.f, 1.f, 1.f, 1.f},
		{0.f, 1.f, 1.f, 1.f},
	};

	// Array of indices defining the triangles of the mesh
	// Each set of three indices refers to vertices in pyramidPositions and pyramidColors
	// Triangles are defined in a counter-clockwise fashion.
	static std::uint32_t pyramidIndices[] =
	{
		// Front Face (using V0, V1, V2 from pyramidPositions)
		0, 1, 2,

		// Right Face (using V3, V4, V5 from pyramidPositions)
		3, 4, 5,

		// Back Face (using V6, V7, V8 from pyramidPositions)
		6, 7, 8,

		// Left Face (using V9, V10, V11 from pyramidPositions)
		9, 10, 11,

		// Base Face (using V12, V13, V14, V15 from pyramidPositions)
		// First triangle: Back-Left, Front-Right, Back-Right (V12, V14, V13)
		12, 14, 13,
		// Second triangle: Back-Left, Front-Left, Front-Right (V12, V15, V14)
		12, 15, 14,
	};

	// Definition of the Mesh object for the pyramid
	const Mesh pyramid
	{
		{pyramidPositions},
		{pyramidColors},
		pyramidIndices,
		sizeof(pyramidIndices) / sizeof(pyramidIndices[0]), // Total number of indices
	};

} // namespace Rasterizer
