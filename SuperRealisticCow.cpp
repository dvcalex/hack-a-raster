#include"SuperRealisticCow.h" // Assuming this header defines Vector3f, Vector4f, and Mesh

namespace Rasterizer
{
	// --- Vertex Positions ---
	// Defined for various parts of the cow. Each part is a cuboid.
	// Vertices are duplicated for each face of each cuboid part to ensure proper color assignment
	// and distinct rendering, as per the format's implied usage.
	// Each cuboid contributes 24 vertices (6 faces * 4 vertices/face).
	static Vector3f cowPositions[] =
	{
		// --------------------------------------------------------------------
		// Part 1: Main Body - Front Section (Brown with a hint of white)
		// Dimensions: X[-1.5, 0.0], Y[0.0, 1.0], Z[-0.6, 0.6]
		// --------------------------------------------------------------------
		// +X Face (Right Side)
		{ 0.0f, 0.0f, -0.6f}, { 0.0f, 1.0f, -0.6f}, { 0.0f, 0.0f, 0.6f}, { 0.0f, 1.0f, 0.6f}, // 0-3
		// -X Face (Left Side)
		{-1.5f, 0.0f, -0.6f}, {-1.5f, 1.0f, -0.6f}, {-1.5f, 0.0f, 0.6f}, {-1.5f, 1.0f, 0.6f}, // 4-7
		// +Y Face (Top)
		{-1.5f, 1.0f, -0.6f}, { 0.0f, 1.0f, -0.6f}, {-1.5f, 1.0f, 0.6f}, { 0.0f, 1.0f, 0.6f}, // 8-11
		// -Y Face (Bottom)
		{-1.5f, 0.0f, -0.6f}, { 0.0f, 0.0f, -0.6f}, {-1.5f, 0.0f, 0.6f}, { 0.0f, 0.0f, 0.6f}, // 12-15
		// +Z Face (Front)
		{-1.5f, 0.0f, 0.6f}, { 0.0f, 0.0f, 0.6f}, {-1.5f, 1.0f, 0.6f}, { 0.0f, 1.0f, 0.6f}, // 16-19
		// -Z Face (Back)
		{-1.5f, 0.0f, -0.6f}, { 0.0f, 0.0f, -0.6f}, {-1.5f, 1.0f, -0.6f}, { 0.0f, 1.0f, -0.6f},// 20-23

		// --------------------------------------------------------------------
		// Part 2: Main Body - Back Section (White patch)
		// Dimensions: X[0.0, 1.5], Y[0.0, 1.0], Z[-0.6, 0.6]
		// --------------------------------------------------------------------
		// +X Face (Right Side)
		{ 1.5f, 0.0f, -0.6f}, { 1.5f, 1.0f, -0.6f}, { 1.5f, 0.0f, 0.6f}, { 1.5f, 1.0f, 0.6f}, // 24-27
		// -X Face (Left Side - common with Part 1's +X face)
		{ 0.0f, 0.0f, -0.6f}, { 0.0f, 1.0f, -0.6f}, { 0.0f, 0.0f, 0.6f}, { 0.0f, 1.0f, 0.6f}, // 28-31
		// +Y Face (Top)
		{ 0.0f, 1.0f, -0.6f}, { 1.5f, 1.0f, -0.6f}, { 0.0f, 1.0f, 0.6f}, { 1.5f, 1.0f, 0.6f}, // 32-35
		// -Y Face (Bottom)
		{ 0.0f, 0.0f, -0.6f}, { 1.5f, 0.0f, -0.6f}, { 0.0f, 0.0f, 0.6f}, { 1.5f, 0.0f, 0.6f}, // 36-39
		// +Z Face (Front)
		{ 0.0f, 0.0f, 0.6f}, { 1.5f, 0.0f, 0.6f}, { 0.0f, 1.0f, 0.6f}, { 1.5f, 1.0f, 0.6f}, // 40-43
		// -Z Face (Back)
		{ 0.0f, 0.0f, -0.6f}, { 1.5f, 0.0f, -0.6f}, { 0.0f, 1.0f, -0.6f}, { 1.5f, 1.0f, -0.6f},// 44-47

		// --------------------------------------------------------------------
		// Part 3: Neck (Brown) - Connects body to head, slight upward angle.
		// Dimensions: X[1.4, 1.9], Y[0.8, 1.3], Z[-0.2, 0.2]
		// --------------------------------------------------------------------
		// +X Face
		{ 1.9f, 0.8f, -0.2f}, { 1.9f, 1.3f, -0.2f}, { 1.9f, 0.8f, 0.2f}, { 1.9f, 1.3f, 0.2f}, // 48-51
		// -X Face
		{ 1.4f, 0.8f, -0.2f}, { 1.4f, 1.3f, -0.2f}, { 1.4f, 0.8f, 0.2f}, { 1.4f, 1.3f, 0.2f}, // 52-55
		// +Y Face
		{ 1.4f, 1.3f, -0.2f}, { 1.9f, 1.3f, -0.2f}, { 1.4f, 1.3f, 0.2f}, { 1.9f, 1.3f, 0.2f}, // 56-59
		// -Y Face
		{ 1.4f, 0.8f, -0.2f}, { 1.9f, 0.8f, -0.2f}, { 1.4f, 0.8f, 0.2f}, { 1.9f, 0.8f, 0.2f}, // 60-63
		// +Z Face
		{ 1.4f, 0.8f, 0.2f}, { 1.9f, 0.8f, 0.2f}, { 1.4f, 1.3f, 0.2f}, { 1.9f, 1.3f, 0.2f}, // 64-67
		// -Z Face
		{ 1.4f, 0.8f, -0.2f}, { 1.9f, 0.8f, -0.2f}, { 1.4f, 1.3f, -0.2f}, { 1.9f, 1.3f, -0.2f},// 68-71

		// --------------------------------------------------------------------
		// Part 4: Head (White)
		// Dimensions: X[1.8, 2.4], Y[1.1, 1.5], Z[-0.3, 0.3]
		// --------------------------------------------------------------------
		// +X Face
		{ 2.4f, 1.1f, -0.3f}, { 2.4f, 1.5f, -0.3f}, { 2.4f, 1.1f, 0.3f}, { 2.4f, 1.5f, 0.3f}, // 72-75
		// -X Face (connected to neck)
		{ 1.8f, 1.1f, -0.3f}, { 1.8f, 1.5f, -0.3f}, { 1.8f, 1.1f, 0.3f}, { 1.8f, 1.5f, 0.3f}, // 76-79
		// +Y Face
		{ 1.8f, 1.5f, -0.3f}, { 2.4f, 1.5f, -0.3f}, { 1.8f, 1.5f, 0.3f}, { 2.4f, 1.5f, 0.3f}, // 80-83
		// -Y Face
		{ 1.8f, 1.1f, -0.3f}, { 2.4f, 1.1f, -0.3f}, { 1.8f, 1.1f, 0.3f}, { 2.4f, 1.1f, 0.3f}, // 84-87
		// +Z Face
		{ 1.8f, 1.1f, 0.3f}, { 2.4f, 1.1f, 0.3f}, { 1.8f, 1.5f, 0.3f}, { 2.4f, 1.5f, 0.3f}, // 88-91
		// -Z Face
		{ 1.8f, 1.1f, -0.3f}, { 2.4f, 1.1f, -0.3f}, { 1.8f, 1.5f, -0.3f}, { 2.4f, 1.5f, -0.3f},// 92-95

		// --------------------------------------------------------------------
		// Part 5: Snout (Pink)
		// Dimensions: X[2.3, 2.7], Y[1.0, 1.2], Z[-0.2, 0.2]
		// --------------------------------------------------------------------
		// +X Face
		{ 2.7f, 1.0f, -0.2f}, { 2.7f, 1.2f, -0.2f}, { 2.7f, 1.0f, 0.2f}, { 2.7f, 1.2f, 0.2f}, // 96-99
		// -X Face (connected to head)
		{ 2.3f, 1.0f, -0.2f}, { 2.3f, 1.2f, -0.2f}, { 2.3f, 1.0f, 0.2f}, { 2.3f, 1.2f, 0.2f}, // 100-103
		// +Y Face
		{ 2.3f, 1.2f, -0.2f}, { 2.7f, 1.2f, -0.2f}, { 2.3f, 1.2f, 0.2f}, { 2.7f, 1.2f, 0.2f}, // 104-107
		// -Y Face
		{ 2.3f, 1.0f, -0.2f}, { 2.7f, 1.0f, -0.2f}, { 2.3f, 1.0f, 0.2f}, { 2.7f, 1.0f, 0.2f}, // 108-111
		// +Z Face
		{ 2.3f, 1.0f, 0.2f}, { 2.7f, 1.0f, 0.2f}, { 2.3f, 1.2f, 0.2f}, { 2.7f, 1.2f, 0.2f}, // 112-115
		// -Z Face
		{ 2.3f, 1.0f, -0.2f}, { 2.7f, 1.0f, -0.2f}, { 2.3f, 1.2f, -0.2f}, { 2.7f, 1.2f, -0.2f},// 116-119

		// --------------------------------------------------------------------
		// Part 6: Left Ear (Pink)
		// Dimensions: X[2.1, 2.3], Y[1.5, 1.7], Z[-0.4, -0.3]
		// --------------------------------------------------------------------
		// +X Face
		{ 2.3f, 1.5f, -0.4f}, { 2.3f, 1.7f, -0.4f}, { 2.3f, 1.5f, -0.3f}, { 2.3f, 1.7f, -0.3f}, // 120-123
		// -X Face
		{ 2.1f, 1.5f, -0.4f}, { 2.1f, 1.7f, -0.4f}, { 2.1f, 1.5f, -0.3f}, { 2.1f, 1.7f, -0.3f}, // 124-127
		// +Y Face
		{ 2.1f, 1.7f, -0.4f}, { 2.3f, 1.7f, -0.4f}, { 2.1f, 1.7f, -0.3f}, { 2.3f, 1.7f, -0.3f}, // 128-131
		// -Y Face
		{ 2.1f, 1.5f, -0.4f}, { 2.3f, 1.5f, -0.4f}, { 2.1f, 1.5f, -0.3f}, { 2.3f, 1.5f, -0.3f}, // 132-135
		// +Z Face
		{ 2.1f, 1.5f, -0.3f}, { 2.3f, 1.5f, -0.3f}, { 2.1f, 1.7f, -0.3f}, { 2.3f, 1.7f, -0.3f}, // 136-139
		// -Z Face
		{ 2.1f, 1.5f, -0.4f}, { 2.3f, 1.5f, -0.4f}, { 2.1f, 1.7f, -0.4f}, { 2.3f, 1.7f, -0.4f}, // 140-143

		// --------------------------------------------------------------------
		// Part 7: Right Ear (Pink)
		// Dimensions: X[2.1, 2.3], Y[1.5, 1.7], Z[0.3, 0.4]
		// --------------------------------------------------------------------
		// +X Face
		{ 2.3f, 1.5f, 0.3f}, { 2.3f, 1.7f, 0.3f}, { 2.3f, 1.5f, 0.4f}, { 2.3f, 1.7f, 0.4f}, // 144-147
		// -X Face
		{ 2.1f, 1.5f, 0.3f}, { 2.1f, 1.7f, 0.3f}, { 2.1f, 1.5f, 0.4f}, { 2.1f, 1.7f, 0.4f}, // 148-151
		// +Y Face
		{ 2.1f, 1.7f, 0.3f}, { 2.3f, 1.7f, 0.3f}, { 2.1f, 1.7f, 0.4f}, { 2.3f, 1.7f, 0.4f}, // 152-155
		// -Y Face
		{ 2.1f, 1.5f, 0.3f}, { 2.3f, 1.5f, 0.3f}, { 2.1f, 1.5f, 0.4f}, { 2.3f, 1.5f, 0.4f}, // 156-159
		// +Z Face
		{ 2.1f, 1.5f, 0.4f}, { 2.3f, 1.5f, 0.4f}, { 2.1f, 1.7f, 0.4f}, { 2.3f, 1.7f, 0.4f}, // 160-163
		// -Z Face
		{ 2.1f, 1.5f, 0.3f}, { 2.3f, 1.5f, 0.3f}, { 2.1f, 1.7f, 0.3f}, { 2.3f, 1.7f, 0.3f}, // 164-167

		// --------------------------------------------------------------------
		// Part 8: Left Horn (Grey)
		// Dimensions: X[2.2, 2.4], Y[1.6, 1.9], Z[-0.25, -0.15] - sloped slightly
		// --------------------------------------------------------------------
		// +X Face
		{ 2.4f, 1.6f, -0.25f}, { 2.4f, 1.9f, -0.15f}, { 2.4f, 1.6f, -0.15f}, { 2.4f, 1.9f, -0.05f}, // 168-171 (Adjusted Y/Z for slope)
		// -X Face
		{ 2.2f, 1.6f, -0.25f}, { 2.2f, 1.9f, -0.15f}, { 2.2f, 1.6f, -0.15f}, { 2.2f, 1.9f, -0.05f}, // 172-175
		// +Y Face (top - angled)
		{ 2.2f, 1.9f, -0.15f}, { 2.4f, 1.9f, -0.15f}, { 2.2f, 1.9f, -0.05f}, { 2.4f, 1.9f, -0.05f}, // 176-179
		// -Y Face (bottom - angled)
		{ 2.2f, 1.6f, -0.25f}, { 2.4f, 1.6f, -0.25f}, { 2.2f, 1.6f, -0.15f}, { 2.4f, 1.6f, -0.15f}, // 180-183
		// +Z Face
		{ 2.2f, 1.6f, -0.15f}, { 2.4f, 1.6f, -0.15f}, { 2.2f, 1.9f, -0.05f}, { 2.4f, 1.9f, -0.05f}, // 184-187
		// -Z Face
		{ 2.2f, 1.6f, -0.25f}, { 2.4f, 1.6f, -0.25f}, { 2.2f, 1.9f, -0.15f}, { 2.4f, 1.9f, -0.15f}, // 188-191

		// --------------------------------------------------------------------
		// Part 9: Right Horn (Grey)
		// Dimensions: X[2.2, 2.4], Y[1.6, 1.9], Z[0.15, 0.25] - sloped slightly
		// --------------------------------------------------------------------
		// +X Face
		{ 2.4f, 1.6f, 0.15f}, { 2.4f, 1.9f, 0.25f}, { 2.4f, 1.6f, 0.25f}, { 2.4f, 1.9f, 0.35f}, // 192-195 (Adjusted Y/Z for slope)
		// -X Face
		{ 2.2f, 1.6f, 0.15f}, { 2.2f, 1.9f, 0.25f}, { 2.2f, 1.6f, 0.25f}, { 2.2f, 1.9f, 0.35f}, // 196-199
		// +Y Face (top - angled)
		{ 2.2f, 1.9f, 0.25f}, { 2.4f, 1.9f, 0.25f}, { 2.2f, 1.9f, 0.35f}, { 2.4f, 1.9f, 0.35f}, // 200-203
		// -Y Face (bottom - angled)
		{ 2.2f, 1.6f, 0.15f}, { 2.4f, 1.6f, 0.15f}, { 2.2f, 1.6f, 0.25f}, { 2.4f, 1.6f, 0.25f}, // 204-207
		// +Z Face
		{ 2.2f, 1.6f, 0.25f}, { 2.4f, 1.6f, 0.25f}, { 2.2f, 1.9f, 0.35f}, { 2.4f, 1.9f, 0.35f}, // 208-211
		// -Z Face
		{ 2.2f, 1.6f, 0.15f}, { 2.4f, 1.6f, 0.15f}, { 2.2f, 1.9f, 0.25f}, { 2.4f, 1.9f, 0.25f}, // 212-215

		// --------------------------------------------------------------------
		// Part 10: Front Left Leg (Black)
		// Dimensions: X[-0.9, -0.7], Y[-1.0, 0.0], Z[0.5, 0.7]
		// --------------------------------------------------------------------
		// +X Face
		{-0.7f, -1.0f, 0.5f}, {-0.7f, 0.0f, 0.5f}, {-0.7f, -1.0f, 0.7f}, {-0.7f, 0.0f, 0.7f}, // 216-219
		// -X Face
		{-0.9f, -1.0f, 0.5f}, {-0.9f, 0.0f, 0.5f}, {-0.9f, -1.0f, 0.7f}, {-0.9f, 0.0f, 0.7f}, // 220-223
		// +Y Face (connected to body)
		{-0.9f, 0.0f, 0.5f}, {-0.7f, 0.0f, 0.5f}, {-0.9f, 0.0f, 0.7f}, {-0.7f, 0.0f, 0.7f}, // 224-227
		// -Y Face (Bottom)
		{-0.9f, -1.0f, 0.5f}, {-0.7f, -1.0f, 0.5f}, {-0.9f, -1.0f, 0.7f}, {-0.7f, -1.0f, 0.7f}, // 228-231
		// +Z Face
		{-0.9f, -1.0f, 0.7f}, {-0.7f, -1.0f, 0.7f}, {-0.9f, 0.0f, 0.7f}, {-0.7f, 0.0f, 0.7f}, // 232-235
		// -Z Face
		{-0.9f, -1.0f, 0.5f}, {-0.7f, -1.0f, 0.5f}, {-0.9f, 0.0f, 0.5f}, {-0.7f, 0.0f, 0.5f}, // 236-239

		// --------------------------------------------------------------------
		// Part 11: Front Right Leg (Black)
		// Dimensions: X[0.7, 0.9], Y[-1.0, 0.0], Z[0.5, 0.7]
		// --------------------------------------------------------------------
		// +X Face
		{ 0.9f, -1.0f, 0.5f}, { 0.9f, 0.0f, 0.5f}, { 0.9f, -1.0f, 0.7f}, { 0.9f, 0.0f, 0.7f}, // 240-243
		// -X Face
		{ 0.7f, -1.0f, 0.5f}, { 0.7f, 0.0f, 0.5f}, { 0.7f, -1.0f, 0.7f}, { 0.7f, 0.0f, 0.7f}, // 244-247
		// +Y Face (connected to body)
		{ 0.7f, 0.0f, 0.5f}, { 0.9f, 0.0f, 0.5f}, { 0.7f, 0.0f, 0.7f}, { 0.9f, 0.0f, 0.7f}, // 248-251
		// -Y Face
		{ 0.7f, -1.0f, 0.5f}, { 0.9f, -1.0f, 0.5f}, { 0.7f, -1.0f, 0.7f}, { 0.9f, -1.0f, 0.7f}, // 252-255
		// +Z Face
		{ 0.7f, -1.0f, 0.7f}, { 0.9f, -1.0f, 0.7f}, { 0.7f, 0.0f, 0.7f}, { 0.9f, 0.0f, 0.7f}, // 256-259
		// -Z Face
		{ 0.7f, -1.0f, 0.5f}, { 0.9f, -1.0f, 0.5f}, { 0.7f, 0.0f, 0.5f}, { 0.9f, 0.0f, 0.5f}, // 260-263

		// --------------------------------------------------------------------
		// Part 12: Back Left Leg (Black)
		// Dimensions: X[-0.9, -0.7], Y[-1.0, 0.0], Z[-0.7, -0.5]
		// --------------------------------------------------------------------
		// +X Face
		{-0.7f, -1.0f, -0.7f}, {-0.7f, 0.0f, -0.7f}, {-0.7f, -1.0f, -0.5f}, {-0.7f, 0.0f, -0.5f}, // 264-267
		// -X Face
		{-0.9f, -1.0f, -0.7f}, {-0.9f, 0.0f, -0.7f}, {-0.9f, -1.0f, -0.5f}, {-0.9f, 0.0f, -0.5f}, // 268-271
		// +Y Face (connected to body)
		{-0.9f, 0.0f, -0.7f}, {-0.7f, 0.0f, -0.7f}, {-0.9f, 0.0f, -0.5f}, {-0.7f, 0.0f, -0.5f}, // 272-275
		// -Y Face
		{-0.9f, -1.0f, -0.7f}, {-0.7f, -1.0f, -0.7f}, {-0.9f, -1.0f, -0.5f}, {-0.7f, -1.0f, -0.5f}, // 276-279
		// +Z Face
		{-0.9f, -1.0f, -0.5f}, {-0.7f, -1.0f, -0.5f}, {-0.9f, 0.0f, -0.5f}, {-0.7f, 0.0f, -0.5f}, // 280-283
		// -Z Face
		{-0.9f, -1.0f, -0.7f}, {-0.7f, -1.0f, -0.7f}, {-0.9f, 0.0f, -0.7f}, {-0.7f, 0.0f, -0.7f}, // 284-287

		// --------------------------------------------------------------------
		// Part 13: Back Right Leg (Black)
		// Dimensions: X[0.7, 0.9], Y[-1.0, 0.0], Z[-0.7, -0.5]
		// --------------------------------------------------------------------
		// +X Face
		{ 0.9f, -1.0f, -0.7f}, { 0.9f, 0.0f, -0.7f}, { 0.9f, -1.0f, -0.5f}, { 0.9f, 0.0f, -0.5f}, // 288-291
		// -X Face
		{ 0.7f, -1.0f, -0.7f}, { 0.7f, 0.0f, -0.7f}, { 0.7f, -1.0f, -0.5f}, { 0.7f, 0.0f, -0.5f}, // 292-295
		// +Y Face (connected to body)
		{ 0.7f, 0.0f, -0.7f}, { 0.9f, 0.0f, -0.7f}, { 0.7f, 0.0f, -0.5f}, { 0.9f, 0.0f, -0.5f}, // 296-299
		// -Y Face
		{ 0.7f, -1.0f, -0.7f}, { 0.9f, -1.0f, -0.7f}, { 0.7f, -1.0f, -0.5f}, { 0.9f, -1.0f, -0.5f}, // 300-303
		// +Z Face
		{ 0.7f, -1.0f, -0.5f}, { 0.9f, -1.0f, -0.5f}, { 0.7f, 0.0f, -0.5f}, { 0.9f, 0.0f, -0.5f}, // 304-307
		// -Z Face
		{ 0.7f, -1.0f, -0.7f}, { 0.9f, -1.0f, -0.7f}, { 0.7f, 0.0f, -0.7f}, { 0.9f, 0.0f, -0.7f}, // 308-311

		// --------------------------------------------------------------------
		// Part 14: Tail (Brown)
		// Dimensions: X[-1.5, -2.0], Y[0.8, 0.6], Z[-0.05, 0.05] (slight downward slope)
		// --------------------------------------------------------------------
		// +X Face
		{-1.5f, 0.8f, -0.05f}, {-1.5f, 0.6f, -0.05f}, {-1.5f, 0.8f, 0.05f}, {-1.5f, 0.6f, 0.05f}, // 312-315
		// -X Face
		{-2.0f, 0.6f, -0.05f}, {-2.0f, 0.4f, -0.05f}, {-2.0f, 0.6f, 0.05f}, {-2.0f, 0.4f, 0.05f}, // 316-319 (Tail tip is lower)
		// +Y Face (top - angled)
		{-1.5f, 0.8f, -0.05f}, {-2.0f, 0.6f, -0.05f}, {-1.5f, 0.8f, 0.05f}, {-2.0f, 0.6f, 0.05f}, // 320-323
		// -Y Face (bottom - angled)
		{-1.5f, 0.6f, -0.05f}, {-2.0f, 0.4f, -0.05f}, {-1.5f, 0.6f, 0.05f}, {-2.0f, 0.4f, 0.05f}, // 324-327
		// +Z Face
		{-1.5f, 0.8f, 0.05f}, {-2.0f, 0.6f, 0.05f}, {-1.5f, 0.6f, 0.05f}, {-2.0f, 0.4f, 0.05f}, // 328-331
		// -Z Face
		{-1.5f, 0.8f, -0.05f}, {-2.0f, 0.6f, -0.05f}, {-1.5f, 0.6f, -0.05f}, {-2.0f, 0.4f, -0.05f},// 332-335
	};

	// --- Vertex Colors ---
	// Each block of 24 entries corresponds to the 24 vertices of a cuboid part.
	static Vector4f cowColors[] =
	{
		// Part 1: Main Body - Front Section (Brown)
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},

		// Part 2: Main Body - Back Section (White)
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},

		// Part 3: Neck (Brown)
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},

		// Part 4: Head (White)
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f},

		// Part 5: Snout (Pink)
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},

		// Part 6: Left Ear (Pink)
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},

		// Part 7: Right Ear (Pink)
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},
		{0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f}, {0.9f, 0.6f, 0.6f, 1.0f},

		// Part 8: Left Horn (Grey)
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},

		// Part 9: Right Horn (Grey)
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},
		{0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f}, {0.7f, 0.7f, 0.7f, 1.0f},

		// Part 10: Front Left Leg (Black)
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},

		// Part 11: Front Right Leg (Black)
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},

		// Part 12: Back Left Leg (Black)
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},

		// Part 13: Back Right Leg (Black)
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f}, {0.1f, 0.1f, 0.1f, 1.0f},

		// Part 14: Tail (Brown)
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
		{0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f}, {0.5f, 0.3f, 0.1f, 1.0f},
	};

	// --- Indices for triangles ---
	// Each cuboid uses 36 indices (6 faces * 2 triangles/face * 3 indices/triangle).
	// The indices are offset for each subsequent part to point to its respective vertex block.
	static std::uint32_t cowIndices[] =
	{
		// --------------------------------------------------------------------
		// Indices for Main Body - Front Section (starts at vertex 0)
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
		   // Indices for Main Body - Back Section (starts at vertex 24)
		   // --------------------------------------------------------------------
		   // Base offset for this part's vertices
		   #define OFFSET_PART2 24
		   // +X face
		   OFFSET_PART2 + 0, OFFSET_PART2 + 2, OFFSET_PART2 + 1, OFFSET_PART2 + 1, OFFSET_PART2 + 2, OFFSET_PART2 + 3,
		   // -X face
		   OFFSET_PART2 + 4, OFFSET_PART2 + 5, OFFSET_PART2 + 6, OFFSET_PART2 + 6, OFFSET_PART2 + 5, OFFSET_PART2 + 7,
		   // +Y face
		   OFFSET_PART2 + 8, OFFSET_PART2 + 9, OFFSET_PART2 + 10, OFFSET_PART2 + 10, OFFSET_PART2 + 9, OFFSET_PART2 + 11,
		   // -Y face
		   OFFSET_PART2 + 12, OFFSET_PART2 + 13, OFFSET_PART2 + 14, OFFSET_PART2 + 14, OFFSET_PART2 + 13, OFFSET_PART2 + 15,
		   // +Z face
		   OFFSET_PART2 + 16, OFFSET_PART2 + 17, OFFSET_PART2 + 18, OFFSET_PART2 + 18, OFFSET_PART2 + 17, OFFSET_PART2 + 19,
		   // -Z face
		   OFFSET_PART2 + 20, OFFSET_PART2 + 21, OFFSET_PART2 + 22, OFFSET_PART2 + 22, OFFSET_PART2 + 21, OFFSET_PART2 + 23,
		   #undef OFFSET_PART2

		   // --------------------------------------------------------------------
		   // Indices for Neck (starts at vertex 48)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART3 48
		   // +X face
		   OFFSET_PART3 + 0, OFFSET_PART3 + 2, OFFSET_PART3 + 1, OFFSET_PART3 + 1, OFFSET_PART3 + 2, OFFSET_PART3 + 3,
		   // -X face
		   OFFSET_PART3 + 4, OFFSET_PART3 + 5, OFFSET_PART3 + 6, OFFSET_PART3 + 6, OFFSET_PART3 + 5, OFFSET_PART3 + 7,
		   // +Y face
		   OFFSET_PART3 + 8, OFFSET_PART3 + 9, OFFSET_PART3 + 10, OFFSET_PART3 + 10, OFFSET_PART3 + 9, OFFSET_PART3 + 11,
		   // -Y face
		   OFFSET_PART3 + 12, OFFSET_PART3 + 13, OFFSET_PART3 + 14, OFFSET_PART3 + 14, OFFSET_PART3 + 13, OFFSET_PART3 + 15,
		   // +Z face
		   OFFSET_PART3 + 16, OFFSET_PART3 + 17, OFFSET_PART3 + 18, OFFSET_PART3 + 18, OFFSET_PART3 + 17, OFFSET_PART3 + 19,
		   // -Z face
		   OFFSET_PART3 + 20, OFFSET_PART3 + 21, OFFSET_PART3 + 22, OFFSET_PART3 + 22, OFFSET_PART3 + 21, OFFSET_PART3 + 23,
		   #undef OFFSET_PART3

		   // --------------------------------------------------------------------
		   // Indices for Head (starts at vertex 72)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART4 72
		   // +X face
		   OFFSET_PART4 + 0, OFFSET_PART4 + 2, OFFSET_PART4 + 1, OFFSET_PART4 + 1, OFFSET_PART4 + 2, OFFSET_PART4 + 3,
		   // -X face
		   OFFSET_PART4 + 4, OFFSET_PART4 + 5, OFFSET_PART4 + 6, OFFSET_PART4 + 6, OFFSET_PART4 + 5, OFFSET_PART4 + 7,
		   // +Y face
		   OFFSET_PART4 + 8, OFFSET_PART4 + 9, OFFSET_PART4 + 10, OFFSET_PART4 + 10, OFFSET_PART4 + 9, OFFSET_PART4 + 11,
		   // -Y face
		   OFFSET_PART4 + 12, OFFSET_PART4 + 13, OFFSET_PART4 + 14, OFFSET_PART4 + 14, OFFSET_PART4 + 13, OFFSET_PART4 + 15,
		   // +Z face
		   OFFSET_PART4 + 16, OFFSET_PART4 + 17, OFFSET_PART4 + 18, OFFSET_PART4 + 18, OFFSET_PART4 + 17, OFFSET_PART4 + 19,
		   // -Z face
		   OFFSET_PART4 + 20, OFFSET_PART4 + 21, OFFSET_PART4 + 22, OFFSET_PART4 + 22, OFFSET_PART4 + 21, OFFSET_PART4 + 23,
		   #undef OFFSET_PART4

		   // --------------------------------------------------------------------
		   // Indices for Snout (starts at vertex 96)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART5 96
		   // +X face
		   OFFSET_PART5 + 0, OFFSET_PART5 + 2, OFFSET_PART5 + 1, OFFSET_PART5 + 1, OFFSET_PART5 + 2, OFFSET_PART5 + 3,
		   // -X face
		   OFFSET_PART5 + 4, OFFSET_PART5 + 5, OFFSET_PART5 + 6, OFFSET_PART5 + 6, OFFSET_PART5 + 5, OFFSET_PART5 + 7,
		   // +Y face
		   OFFSET_PART5 + 8, OFFSET_PART5 + 9, OFFSET_PART5 + 10, OFFSET_PART5 + 10, OFFSET_PART5 + 9, OFFSET_PART5 + 11,
		   // -Y face
		   OFFSET_PART5 + 12, OFFSET_PART5 + 13, OFFSET_PART5 + 14, OFFSET_PART5 + 14, OFFSET_PART5 + 13, OFFSET_PART5 + 15,
		   // +Z face
		   OFFSET_PART5 + 16, OFFSET_PART5 + 17, OFFSET_PART5 + 18, OFFSET_PART5 + 18, OFFSET_PART5 + 17, OFFSET_PART5 + 19,
		   // -Z face
		   OFFSET_PART5 + 20, OFFSET_PART5 + 21, OFFSET_PART5 + 22, OFFSET_PART5 + 22, OFFSET_PART5 + 21, OFFSET_PART5 + 23,
		   #undef OFFSET_PART5

		   // --------------------------------------------------------------------
		   // Indices for Left Ear (starts at vertex 120)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART6 120
		   // +X face
		   OFFSET_PART6 + 0, OFFSET_PART6 + 2, OFFSET_PART6 + 1, OFFSET_PART6 + 1, OFFSET_PART6 + 2, OFFSET_PART6 + 3,
		   // -X face
		   OFFSET_PART6 + 4, OFFSET_PART6 + 5, OFFSET_PART6 + 6, OFFSET_PART6 + 6, OFFSET_PART6 + 5, OFFSET_PART6 + 7,
		   // +Y face
		   OFFSET_PART6 + 8, OFFSET_PART6 + 9, OFFSET_PART6 + 10, OFFSET_PART6 + 10, OFFSET_PART6 + 9, OFFSET_PART6 + 11,
		   // -Y face
		   OFFSET_PART6 + 12, OFFSET_PART6 + 13, OFFSET_PART6 + 14, OFFSET_PART6 + 14, OFFSET_PART6 + 13, OFFSET_PART6 + 15,
		   // +Z face
		   OFFSET_PART6 + 16, OFFSET_PART6 + 17, OFFSET_PART6 + 18, OFFSET_PART6 + 18, OFFSET_PART6 + 17, OFFSET_PART6 + 19,
		   // -Z face
		   OFFSET_PART6 + 20, OFFSET_PART6 + 21, OFFSET_PART6 + 22, OFFSET_PART6 + 22, OFFSET_PART6 + 21, OFFSET_PART6 + 23,
		   #undef OFFSET_PART6

		   // --------------------------------------------------------------------
		   // Indices for Right Ear (starts at vertex 144)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART7 144
		   // +X face
		   OFFSET_PART7 + 0, OFFSET_PART7 + 2, OFFSET_PART7 + 1, OFFSET_PART7 + 1, OFFSET_PART7 + 2, OFFSET_PART7 + 3,
		   // -X face
		   OFFSET_PART7 + 4, OFFSET_PART7 + 5, OFFSET_PART7 + 6, OFFSET_PART7 + 6, OFFSET_PART7 + 5, OFFSET_PART7 + 7,
		   // +Y face
		   OFFSET_PART7 + 8, OFFSET_PART7 + 9, OFFSET_PART7 + 10, OFFSET_PART7 + 10, OFFSET_PART7 + 9, OFFSET_PART7 + 11,
		   // -Y face
		   OFFSET_PART7 + 12, OFFSET_PART7 + 13, OFFSET_PART7 + 14, OFFSET_PART7 + 14, OFFSET_PART7 + 13, OFFSET_PART7 + 15,
		   // +Z face
		   OFFSET_PART7 + 16, OFFSET_PART7 + 17, OFFSET_PART7 + 18, OFFSET_PART7 + 18, OFFSET_PART7 + 17, OFFSET_PART7 + 19,
		   // -Z face
		   OFFSET_PART7 + 20, OFFSET_PART7 + 21, OFFSET_PART7 + 22, OFFSET_PART7 + 22, OFFSET_PART7 + 21, OFFSET_PART7 + 23,
		   #undef OFFSET_PART7

		   // --------------------------------------------------------------------
		   // Indices for Left Horn (starts at vertex 168)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART8 168
		   // +X face
		   OFFSET_PART8 + 0, OFFSET_PART8 + 2, OFFSET_PART8 + 1, OFFSET_PART8 + 1, OFFSET_PART8 + 2, OFFSET_PART8 + 3,
		   // -X face
		   OFFSET_PART8 + 4, OFFSET_PART8 + 5, OFFSET_PART8 + 6, OFFSET_PART8 + 6, OFFSET_PART8 + 5, OFFSET_PART8 + 7,
		   // +Y face
		   OFFSET_PART8 + 8, OFFSET_PART8 + 9, OFFSET_PART8 + 10, OFFSET_PART8 + 10, OFFSET_PART8 + 9, OFFSET_PART8 + 11,
		   // -Y face
		   OFFSET_PART8 + 12, OFFSET_PART8 + 13, OFFSET_PART8 + 14, OFFSET_PART8 + 14, OFFSET_PART8 + 13, OFFSET_PART8 + 15,
		   // +Z face
		   OFFSET_PART8 + 16, OFFSET_PART8 + 17, OFFSET_PART8 + 18, OFFSET_PART8 + 18, OFFSET_PART8 + 17, OFFSET_PART8 + 19,
		   // -Z face
		   OFFSET_PART8 + 20, OFFSET_PART8 + 21, OFFSET_PART8 + 22, OFFSET_PART8 + 22, OFFSET_PART8 + 21, OFFSET_PART8 + 23,
		   #undef OFFSET_PART8

		   // --------------------------------------------------------------------
		   // Indices for Right Horn (starts at vertex 192)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART9 192
		   // +X face
		   OFFSET_PART9 + 0, OFFSET_PART9 + 2, OFFSET_PART9 + 1, OFFSET_PART9 + 1, OFFSET_PART9 + 2, OFFSET_PART9 + 3,
		   // -X face
		   OFFSET_PART9 + 4, OFFSET_PART9 + 5, OFFSET_PART9 + 6, OFFSET_PART9 + 6, OFFSET_PART9 + 5, OFFSET_PART9 + 7,
		   // +Y face
		   OFFSET_PART9 + 8, OFFSET_PART9 + 9, OFFSET_PART9 + 10, OFFSET_PART9 + 10, OFFSET_PART9 + 9, OFFSET_PART9 + 11,
		   // -Y face
		   OFFSET_PART9 + 12, OFFSET_PART9 + 13, OFFSET_PART9 + 14, OFFSET_PART9 + 14, OFFSET_PART9 + 13, OFFSET_PART9 + 15,
		   // +Z face
		   OFFSET_PART9 + 16, OFFSET_PART9 + 17, OFFSET_PART9 + 18, OFFSET_PART9 + 18, OFFSET_PART9 + 17, OFFSET_PART9 + 19,
		   // -Z face
		   OFFSET_PART9 + 20, OFFSET_PART9 + 21, OFFSET_PART9 + 22, OFFSET_PART9 + 22, OFFSET_PART9 + 21, OFFSET_PART9 + 23,
		   #undef OFFSET_PART9

		   // --------------------------------------------------------------------
		   // Indices for Front Left Leg (starts at vertex 216)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART10 216
		   // +X face
		   OFFSET_PART10 + 0, OFFSET_PART10 + 2, OFFSET_PART10 + 1, OFFSET_PART10 + 1, OFFSET_PART10 + 2, OFFSET_PART10 + 3,
		   // -X face
		   OFFSET_PART10 + 4, OFFSET_PART10 + 5, OFFSET_PART10 + 6, OFFSET_PART10 + 6, OFFSET_PART10 + 5, OFFSET_PART10 + 7,
		   // +Y face
		   OFFSET_PART10 + 8, OFFSET_PART10 + 9, OFFSET_PART10 + 10, OFFSET_PART10 + 10, OFFSET_PART10 + 9, OFFSET_PART10 + 11,
		   // -Y face
		   OFFSET_PART10 + 12, OFFSET_PART10 + 13, OFFSET_PART10 + 14, OFFSET_PART10 + 14, OFFSET_PART10 + 13, OFFSET_PART10 + 15,
		   // +Z face
		   OFFSET_PART10 + 16, OFFSET_PART10 + 17, OFFSET_PART10 + 18, OFFSET_PART10 + 18, OFFSET_PART10 + 17, OFFSET_PART10 + 19,
		   // -Z face
		   OFFSET_PART10 + 20, OFFSET_PART10 + 21, OFFSET_PART10 + 22, OFFSET_PART10 + 22, OFFSET_PART10 + 21, OFFSET_PART10 + 23,
		   #undef OFFSET_PART10

		   // --------------------------------------------------------------------
		   // Indices for Front Right Leg (starts at vertex 240)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART11 240
		   // +X face
		   OFFSET_PART11 + 0, OFFSET_PART11 + 2, OFFSET_PART11 + 1, OFFSET_PART11 + 1, OFFSET_PART11 + 2, OFFSET_PART11 + 3,
		   // -X face
		   OFFSET_PART11 + 4, OFFSET_PART11 + 5, OFFSET_PART11 + 6, OFFSET_PART11 + 6, OFFSET_PART11 + 5, OFFSET_PART11 + 7,
		   // +Y face
		   OFFSET_PART11 + 8, OFFSET_PART11 + 9, OFFSET_PART11 + 10, OFFSET_PART11 + 10, OFFSET_PART11 + 9, OFFSET_PART11 + 11,
		   // -Y face
		   OFFSET_PART11 + 12, OFFSET_PART11 + 13, OFFSET_PART11 + 14, OFFSET_PART11 + 14, OFFSET_PART11 + 13, OFFSET_PART11 + 15,
		   // +Z face
		   OFFSET_PART11 + 16, OFFSET_PART11 + 17, OFFSET_PART11 + 18, OFFSET_PART11 + 18, OFFSET_PART11 + 17, OFFSET_PART11 + 19,
		   // -Z face
		   OFFSET_PART11 + 20, OFFSET_PART11 + 21, OFFSET_PART11 + 22, OFFSET_PART11 + 22, OFFSET_PART11 + 21, OFFSET_PART11 + 23,
		   #undef OFFSET_PART11

		   // --------------------------------------------------------------------
		   // Indices for Back Left Leg (starts at vertex 264)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART12 264
		   // +X face
		   OFFSET_PART12 + 0, OFFSET_PART12 + 2, OFFSET_PART12 + 1, OFFSET_PART12 + 1, OFFSET_PART12 + 2, OFFSET_PART12 + 3,
		   // -X face
		   OFFSET_PART12 + 4, OFFSET_PART12 + 5, OFFSET_PART12 + 6, OFFSET_PART12 + 6, OFFSET_PART12 + 5, OFFSET_PART12 + 7,
		   // +Y face
		   OFFSET_PART12 + 8, OFFSET_PART12 + 9, OFFSET_PART12 + 10, OFFSET_PART12 + 10, OFFSET_PART12 + 9, OFFSET_PART12 + 11,
		   // -Y face
		   OFFSET_PART12 + 12, OFFSET_PART12 + 13, OFFSET_PART12 + 14, OFFSET_PART12 + 14, OFFSET_PART12 + 13, OFFSET_PART12 + 15,
		   // +Z face
		   OFFSET_PART12 + 16, OFFSET_PART12 + 17, OFFSET_PART12 + 18, OFFSET_PART12 + 18, OFFSET_PART12 + 17, OFFSET_PART12 + 19,
		   // -Z face
		   OFFSET_PART12 + 20, OFFSET_PART12 + 21, OFFSET_PART12 + 22, OFFSET_PART12 + 22, OFFSET_PART12 + 21, OFFSET_PART12 + 23,
		   #undef OFFSET_PART12

		   // --------------------------------------------------------------------
		   // Indices for Back Right Leg (starts at vertex 288)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART13 288
		   // +X face
		   OFFSET_PART13 + 0, OFFSET_PART13 + 2, OFFSET_PART13 + 1, OFFSET_PART13 + 1, OFFSET_PART13 + 2, OFFSET_PART13 + 3,
		   // -X face
		   OFFSET_PART13 + 4, OFFSET_PART13 + 5, OFFSET_PART13 + 6, OFFSET_PART13 + 6, OFFSET_PART13 + 5, OFFSET_PART13 + 7,
		   // +Y face
		   OFFSET_PART13 + 8, OFFSET_PART13 + 9, OFFSET_PART13 + 10, OFFSET_PART13 + 10, OFFSET_PART13 + 9, OFFSET_PART13 + 11,
		   // -Y face
		   OFFSET_PART13 + 12, OFFSET_PART13 + 13, OFFSET_PART13 + 14, OFFSET_PART13 + 14, OFFSET_PART13 + 13, OFFSET_PART13 + 15,
		   // +Z face
		   OFFSET_PART13 + 16, OFFSET_PART13 + 17, OFFSET_PART13 + 18, OFFSET_PART13 + 18, OFFSET_PART13 + 17, OFFSET_PART13 + 19,
		   // -Z face
		   OFFSET_PART13 + 20, OFFSET_PART13 + 21, OFFSET_PART13 + 22, OFFSET_PART13 + 22, OFFSET_PART13 + 21, OFFSET_PART13 + 23,
		   #undef OFFSET_PART13

		   // --------------------------------------------------------------------
		   // Indices for Tail (starts at vertex 312)
		   // --------------------------------------------------------------------
		   #define OFFSET_PART14 312
		   // +X face
		   OFFSET_PART14 + 0, OFFSET_PART14 + 2, OFFSET_PART14 + 1, OFFSET_PART14 + 1, OFFSET_PART14 + 2, OFFSET_PART14 + 3,
		   // -X face
		   OFFSET_PART14 + 4, OFFSET_PART14 + 5, OFFSET_PART14 + 6, OFFSET_PART14 + 6, OFFSET_PART14 + 5, OFFSET_PART14 + 7,
		   // +Y face
		   OFFSET_PART14 + 8, OFFSET_PART14 + 9, OFFSET_PART14 + 10, OFFSET_PART14 + 10, OFFSET_PART14 + 9, OFFSET_PART14 + 11,
		   // -Y face
		   OFFSET_PART14 + 12, OFFSET_PART14 + 13, OFFSET_PART14 + 14, OFFSET_PART14 + 14, OFFSET_PART14 + 13, OFFSET_PART14 + 15,
		   // +Z face
		   OFFSET_PART14 + 16, OFFSET_PART14 + 17, OFFSET_PART14 + 18, OFFSET_PART14 + 18, OFFSET_PART14 + 17, OFFSET_PART14 + 19,
		   // -Z face
		   OFFSET_PART14 + 20, OFFSET_PART14 + 21, OFFSET_PART14 + 22, OFFSET_PART14 + 22, OFFSET_PART14 + 21, OFFSET_PART14 + 23,
		   #undef OFFSET_PART14
	};

	// Definition of the Mesh object for the detailed cow
	const Mesh superRealisticCow
	{
		{cowPositions},
		{cowColors},
		cowIndices,
		sizeof(cowIndices) / sizeof(cowIndices[0]), // Total number of indices
	};

} // namespace Rasterizer