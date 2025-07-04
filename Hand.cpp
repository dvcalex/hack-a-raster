#include"Hand.h" // Assuming this header defines Vector3f, Vector4f, and Mesh

namespace Rasterizer
{
	// --- Vertex Positions ---
	// Defined for each part of the human hand. Each part is a cuboid.
	// Vertices are duplicated for distinct parts to allow for independent coloring and easier indexing.
	// Each cuboid has 6 faces * 4 vertices per face = 24 vertex entries.
	static Vector3f humanHandPositions[] =
	{
		// --------------------------------------------------------------------
		// Part 1: Palm (Skin Tone) - Cuboid: X[-0.5, 0.5], Y[-0.8, 0.0], Z[-0.2, 0.2]
		// This is the base from which the fingers extend.
		// --------------------------------------------------------------------
		// +X Face (Right side of palm)
		{ 0.5f, -0.8f, -0.2f}, { 0.5f, 0.0f, -0.2f}, { 0.5f, -0.8f, 0.2f}, { 0.5f, 0.0f, 0.2f},
		// -X Face (Left side of palm)
		{-0.5f, -0.8f, -0.2f}, {-0.5f, 0.0f, -0.2f}, {-0.5f, -0.8f, 0.2f}, {-0.5f, 0.0f, 0.2f},
		// +Y Face (Top of palm - where fingers attach)
		{-0.5f, 0.0f, -0.2f}, { 0.5f, 0.0f, -0.2f}, {-0.5f, 0.0f, 0.2f}, { 0.5f, 0.0f, 0.2f},
		// -Y Face (Bottom of palm)
		{-0.5f, -0.8f, -0.2f}, { 0.5f, -0.8f, -0.2f}, {-0.5f, -0.8f, 0.2f}, { 0.5f, -0.8f, 0.2f},
		// +Z Face (Front of palm - towards fingers)
		{-0.5f, -0.8f, 0.2f}, { 0.5f, -0.8f, 0.2f}, {-0.5f, 0.0f, 0.2f}, { 0.5f, 0.0f, 0.2f},
		// -Z Face (Back of palm - towards wrist)
		{-0.5f, -0.8f, -0.2f}, { 0.5f, -0.8f, -0.2f}, {-0.5f, 0.0f, -0.2f}, { 0.5f, 0.0f, -0.2f},

		// --------------------------------------------------------------------
		// Part 2: Thumb (Skin Tone) - Cuboid: X[-0.6, -0.4], Y[-0.6, -0.1], Z[-0.3, -0.1]
		// Offset and rotated slightly for thumb position
		// --------------------------------------------------------------------
		// +X Face
		{-0.4f, -0.6f, -0.3f}, {-0.4f, -0.1f, -0.3f}, {-0.4f, -0.6f, -0.1f}, {-0.4f, -0.1f, -0.1f},
		// -X Face
		{-0.6f, -0.6f, -0.3f}, {-0.6f, -0.1f, -0.3f}, {-0.6f, -0.6f, -0.1f}, {-0.6f, -0.1f, -0.1f},
		// +Y Face
		{-0.6f, -0.1f, -0.3f}, {-0.4f, -0.1f, -0.3f}, {-0.6f, -0.1f, -0.1f}, {-0.4f, -0.1f, -0.1f},
		// -Y Face
		{-0.6f, -0.6f, -0.3f}, {-0.4f, -0.6f, -0.3f}, {-0.6f, -0.6f, -0.1f}, {-0.4f, -0.6f, -0.1f},
		// +Z Face
		{-0.6f, -0.6f, -0.1f}, {-0.4f, -0.6f, -0.1f}, {-0.6f, -0.1f, -0.1f}, {-0.4f, -0.1f, -0.1f},
		// -Z Face
		{-0.6f, -0.6f, -0.3f}, {-0.4f, -0.6f, -0.3f}, {-0.6f, -0.1f, -0.3f}, {-0.4f, -0.1f, -0.3f},

		// --------------------------------------------------------------------
		// Part 3: Index Finger (Skin Tone) - Cuboid: X[-0.3, -0.1], Y[0.0, 0.6], Z[-0.1, 0.1]
		// --------------------------------------------------------------------
		// +X Face
		{-0.1f, 0.0f, -0.1f}, {-0.1f, 0.6f, -0.1f}, {-0.1f, 0.0f, 0.1f}, {-0.1f, 0.6f, 0.1f},
		// -X Face
		{-0.3f, 0.0f, -0.1f}, {-0.3f, 0.6f, -0.1f}, {-0.3f, 0.0f, 0.1f}, {-0.3f, 0.6f, 0.1f},
		// +Y Face
		{-0.3f, 0.6f, -0.1f}, {-0.1f, 0.6f, -0.1f}, {-0.3f, 0.6f, 0.1f}, {-0.1f, 0.6f, 0.1f},
		// -Y Face
		{-0.3f, 0.0f, -0.1f}, {-0.1f, 0.0f, -0.1f}, {-0.3f, 0.0f, 0.1f}, {-0.1f, 0.0f, 0.1f},
		// +Z Face
		{-0.3f, 0.0f, 0.1f}, {-0.1f, 0.0f, 0.1f}, {-0.3f, 0.6f, 0.1f}, {-0.1f, 0.6f, 0.1f},
		// -Z Face
		{-0.3f, 0.0f, -0.1f}, {-0.1f, 0.0f, -0.1f}, {-0.3f, 0.6f, -0.1f}, {-0.1f, 0.6f, -0.1f},

		// --------------------------------------------------------------------
		// Part 4: Middle Finger (Skin Tone) - Cuboid: X[-0.1, 0.1], Y[0.0, 0.7], Z[-0.1, 0.1]
		// Slightly longer than index
		// --------------------------------------------------------------------
		// +X Face
		{ 0.1f, 0.0f, -0.1f}, { 0.1f, 0.7f, -0.1f}, { 0.1f, 0.0f, 0.1f}, { 0.1f, 0.7f, 0.1f},
		// -X Face
		{-0.1f, 0.0f, -0.1f}, {-0.1f, 0.7f, -0.1f}, {-0.1f, 0.0f, 0.1f}, {-0.1f, 0.7f, 0.1f},
		// +Y Face
		{-0.1f, 0.7f, -0.1f}, { 0.1f, 0.7f, -0.1f}, {-0.1f, 0.7f, 0.1f}, { 0.1f, 0.7f, 0.1f},
		// -Y Face
		{-0.1f, 0.0f, -0.1f}, { 0.1f, 0.0f, -0.1f}, {-0.1f, 0.0f, 0.1f}, { 0.1f, 0.0f, 0.1f},
		// +Z Face
		{-0.1f, 0.0f, 0.1f}, { 0.1f, 0.0f, 0.1f}, {-0.1f, 0.7f, 0.1f}, { 0.1f, 0.7f, 0.1f},
		// -Z Face
		{-0.1f, 0.0f, -0.1f}, { 0.1f, 0.0f, -0.1f}, {-0.1f, 0.7f, -0.1f}, { 0.1f, 0.7f, -0.1f},

		// --------------------------------------------------------------------
		// Part 5: Ring Finger (Skin Tone) - Cuboid: X[0.1, 0.3], Y[0.0, 0.65], Z[-0.1, 0.1]
		// Slightly shorter than middle
		// --------------------------------------------------------------------
		// +X Face
		{ 0.3f, 0.0f, -0.1f}, { 0.3f, 0.65f, -0.1f}, { 0.3f, 0.0f, 0.1f}, { 0.3f, 0.65f, 0.1f},
		// -X Face
		{ 0.1f, 0.0f, -0.1f}, { 0.1f, 0.65f, -0.1f}, { 0.1f, 0.0f, 0.1f}, { 0.1f, 0.65f, 0.1f},
		// +Y Face
		{ 0.1f, 0.65f, -0.1f}, { 0.3f, 0.65f, -0.1f}, { 0.1f, 0.65f, 0.1f}, { 0.3f, 0.65f, 0.1f},
		// -Y Face
		{ 0.1f, 0.0f, -0.1f}, { 0.3f, 0.0f, -0.1f}, { 0.1f, 0.0f, 0.1f}, { 0.3f, 0.0f, 0.1f},
		// +Z Face
		{ 0.1f, 0.0f, 0.1f}, { 0.3f, 0.0f, 0.1f}, { 0.1f, 0.65f, 0.1f}, { 0.3f, 0.65f, 0.1f},
		// -Z Face
		{ 0.1f, 0.0f, -0.1f}, { 0.3f, 0.0f, -0.1f}, { 0.1f, 0.65f, -0.1f}, { 0.3f, 0.65f, -0.1f},

		// --------------------------------------------------------------------
		// Part 6: Pinky Finger (Skin Tone) - Cuboid: X[0.3, 0.5], Y[0.0, 0.55], Z[-0.1, 0.1]
		// Shortest finger
		// --------------------------------------------------------------------
		// +X Face
		{ 0.5f, 0.0f, -0.1f}, { 0.5f, 0.55f, -0.1f}, { 0.5f, 0.0f, 0.1f}, { 0.5f, 0.55f, 0.1f},
		// -X Face
		{ 0.3f, 0.0f, -0.1f}, { 0.3f, 0.55f, -0.1f}, { 0.3f, 0.0f, 0.1f}, { 0.3f, 0.55f, 0.1f},
		// +Y Face
		{ 0.3f, 0.55f, -0.1f}, { 0.5f, 0.55f, -0.1f}, { 0.3f, 0.55f, 0.1f}, { 0.5f, 0.55f, 0.1f},
		// -Y Face
		{ 0.3f, 0.0f, -0.1f}, { 0.5f, 0.0f, -0.1f}, { 0.3f, 0.0f, 0.1f}, { 0.5f, 0.0f, 0.1f},
		// +Z Face
		{ 0.3f, 0.0f, 0.1f}, { 0.5f, 0.0f, 0.1f}, { 0.3f, 0.55f, 0.1f}, { 0.5f, 0.55f, 0.1f},
		// -Z Face
		{ 0.3f, 0.0f, -0.1f}, { 0.5f, 0.0f, -0.1f}, { 0.3f, 0.55f, -0.1f}, { 0.5f, 0.55f, -0.1f},
	};

	// --- Vertex Colors ---
	// All parts are colored with a light skin tone.
	// Each set of 24 entries corresponds to the 24 vertices of a cuboid part.
	static Vector4f humanHandColors[] =
	{
		// Part 1: Palm (Skin Tone)
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},

		// Part 2: Thumb (Skin Tone)
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},

		// Part 3: Index Finger (Skin Tone)
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},

		// Part 4: Middle Finger (Skin Tone)
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},

		// Part 5: Ring Finger (Skin Tone)
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},

		// Part 6: Pinky Finger (Skin Tone)
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
		{0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f}, {0.8f, 0.6f, 0.5f, 1.0f},
	};

	// --- Indices for triangles ---
	// Each cuboid uses 36 indices (6 faces * 2 triangles/face * 3 indices/triangle)
	// The indices are offset for each subsequent part to point to its respective vertex block.
	static std::uint32_t humanHandIndices[] =
	{
		// --------------------------------------------------------------------
		// Indices for Palm (starts at index 0 in humanHandPositions/Colors)
		// --------------------------------------------------------------------
		// +X face
		 0,  2,  1,   1,  2,  3,
		 // -X face
		  4,  5,  6,   6,  5,  7,
		  // +Y face
		   8,  9, 10,  10,  9, 11,
		   // -Y face
		   12, 13, 14,  14, 13, 15,
		   // +Z face
		   16, 17, 18,  18, 17, 19,
		   // -Z face
		   20, 21, 22,  22, 21, 23,

		   // --------------------------------------------------------------------
		   // Indices for Thumb (starts at index 24, offset by 24 for each index)
		   // --------------------------------------------------------------------
		   // +X face
		   24 + 0, 24 + 2, 24 + 1, 24 + 1, 24 + 2, 24 + 3,
		   // -X face
		   24 + 4, 24 + 5, 24 + 6, 24 + 6, 24 + 5, 24 + 7,
		   // +Y face
		   24 + 8, 24 + 9, 24 + 10, 24 + 10, 24 + 9, 24 + 11,
		   // -Y face
		   24 + 12, 24 + 13, 24 + 14, 24 + 14, 24 + 13, 24 + 15,
		   // +Z face
		   24 + 16, 24 + 17, 24 + 18, 24 + 18, 24 + 17, 24 + 19,
		   // -Z face
		   24 + 20, 24 + 21, 24 + 22, 24 + 22, 24 + 21, 24 + 23,

		   // --------------------------------------------------------------------
		   // Indices for Index Finger (starts at index 48, offset by 48)
		   // --------------------------------------------------------------------
		   // +X face
		   48 + 0, 48 + 2, 48 + 1, 48 + 1, 48 + 2, 48 + 3,
		   // -X face
		   48 + 4, 48 + 5, 48 + 6, 48 + 6, 48 + 5, 48 + 7,
		   // +Y face
		   48 + 8, 48 + 9, 48 + 10, 48 + 10, 48 + 9, 48 + 11,
		   // -Y face
		   48 + 12, 48 + 13, 48 + 14, 48 + 14, 48 + 13, 48 + 15,
		   // +Z face
		   48 + 16, 48 + 17, 48 + 18, 48 + 18, 48 + 17, 48 + 19,
		   // -Z face
		   48 + 20, 48 + 21, 48 + 22, 48 + 22, 48 + 21, 48 + 23,

		   // --------------------------------------------------------------------
		   // Indices for Middle Finger (starts at index 72, offset by 72)
		   // --------------------------------------------------------------------
		   // +X face
		   72 + 0, 72 + 2, 72 + 1, 72 + 1, 72 + 2, 72 + 3,
		   // -X face
		   72 + 4, 72 + 5, 72 + 6, 72 + 6, 72 + 5, 72 + 7,
		   // +Y face
		   72 + 8, 72 + 9, 72 + 10, 72 + 10, 72 + 9, 72 + 11,
		   // -Y face
		   72 + 12, 72 + 13, 72 + 14, 72 + 14, 72 + 13, 72 + 15,
		   // +Z face
		   72 + 16, 72 + 17, 72 + 18, 72 + 18, 72 + 17, 72 + 19,
		   // -Z face
		   72 + 20, 72 + 21, 72 + 22, 72 + 22, 72 + 21, 72 + 23,

		   // --------------------------------------------------------------------
		   // Indices for Ring Finger (starts at index 96, offset by 96)
		   // --------------------------------------------------------------------
		   // +X face
		   96 + 0, 96 + 2, 96 + 1, 96 + 1, 96 + 2, 96 + 3,
		   // -X face
		   96 + 4, 96 + 5, 96 + 6, 96 + 6, 96 + 5, 96 + 7,
		   // +Y face
		   96 + 8, 96 + 9, 96 + 10, 96 + 10, 96 + 9, 96 + 11,
		   // -Y face
		   96 + 12, 96 + 13, 96 + 14, 96 + 14, 96 + 13, 96 + 15,
		   // +Z face
		   96 + 16, 96 + 17, 96 + 18, 96 + 18, 96 + 17, 96 + 19,
		   // -Z face
		   96 + 20, 96 + 21, 96 + 22, 96 + 22, 96 + 21, 96 + 23,

		   // --------------------------------------------------------------------
		   // Indices for Pinky Finger (starts at index 120, offset by 120)
		   // --------------------------------------------------------------------
		   // +X face
		   120 + 0, 120 + 2, 120 + 1, 120 + 1, 120 + 2, 120 + 3,
		   // -X face
		   120 + 4, 120 + 5, 120 + 6, 120 + 6, 120 + 5, 120 + 7,
		   // +Y face
		   120 + 8, 120 + 9, 120 + 10, 120 + 10, 120 + 9, 120 + 11,
		   // -Y face
		   120 + 12, 120 + 13, 120 + 14, 120 + 14, 120 + 13, 120 + 15,
		   // +Z face
		   120 + 16, 120 + 17, 120 + 18, 120 + 18, 120 + 17, 120 + 19,
		   // -Z face
		   120 + 20, 120 + 21, 120 + 22, 120 + 22, 120 + 21, 120 + 23,
	};

	// Definition of the Mesh object for the human hand
	const Mesh hand
	{
		{humanHandPositions},
		{humanHandColors},
		humanHandIndices,
		sizeof(humanHandIndices) / sizeof(humanHandIndices[0]), // Total number of indices (6 parts * 36 indices/part)
	};

} // namespace Rasterizer
