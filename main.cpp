/*
* This file is based on public domain SDL example code:
* https://examples.libsdl.org/SDL3/renderer/04-points/
*
* Other parts of this project are based on this tutorial:
* https://lisyarus.github.io/blog/posts/implementing-a-tiny-cpu-rasterizer-part-1.html
*
*
*/

#include"Globals.h" // comes before #ifndef MY_DEBUG

#ifndef MY_DEBUG

#include"Renderer.h"
#include"VertexAttribute.h"
#include"Cube.h"

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <algorithm>
#include <chrono>
#include <iostream>

using myClock = std::chrono::high_resolution_clock;
using Rasterizer::ColorBuffer;

/* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static SDL_Surface* drawSurface = nullptr;

static float mouse_x{ 0 };
static float mouse_y{ 0 };

static std::chrono::steady_clock::time_point lastTick;
static float elapsedTime{ 0 };

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	SDL_SetAppMetadata("From Scratch CPU Rasterizer", "1.0", "com.hack.from-scratch-cpu-rasterizer");

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if (!SDL_CreateWindowAndRenderer("From Scratch CPU Rasterizer", WINDOW_WIDTH, WINDOW_HEIGHT, 0 /* | SDL_WINDOW_RESIZABLE */, &window, &renderer)) \
	{
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if (!drawSurface)
	{
		drawSurface = SDL_CreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_PIXELFORMAT_RGBA32);
		SDL_SetSurfaceBlendMode(drawSurface, SDL_BLENDMODE_NONE);
	}

	/* do any initial setup here */
	lastTick = myClock::now();


	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_EVENT_QUIT:
		/* end the program, reporting success to the OS. */
		return SDL_APP_SUCCESS;
		/*case SDL_EVENT_WINDOW_RESIZED:
			if (drawSurface)
				SDL_DestroySurface(drawSurface);
			drawSurface = nullptr;
			windowWidth = event->window.data1;
			windowHeight = event->window.data2;
			break;*/
	case SDL_EVENT_MOUSE_MOTION:
		mouse_x = event->motion.x;
		mouse_y = event->motion.y;
		break;
	}


	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
	// Handle frame rate count
	auto thisTick{ myClock::now() };
	float dt{ std::chrono::duration_cast<std::chrono::duration<float>>(
		thisTick - lastTick).count() };
	lastTick = thisTick;
#ifdef PROFILE_FPS
	std::cout << "fps : " << (1.f / dt) << std::endl;
#endif
#ifdef PROFILE_DELTATIME
	std::cout << "dt : " << dt << std::endl;
#endif
	elapsedTime += dt;


	// Get pointer to pixels (our buffer)
	ColorBuffer colorBuffer{ (Rasterizer::Color4UB*)drawSurface->pixels };

	// Setup our viewport
	Rasterizer::Viewport viewport
	{
		0,
		0,
		(std::int32_t)WINDOW_WIDTH,
		(std::int32_t)WINDOW_HEIGHT,
	};

	// Clear and set a color
	Rasterizer::Clear(colorBuffer, { 0.8f, 0.9f, 1.f, 1.f });

	// Postions of vertices in NDC (Normalized Device Coordinates)
	Rasterizer::Vector3f positions[]
	{
		{-0.5f, -0.5f, 0.f},
		{-0.5f,  0.5f, 0.f},
		{ 0.5f, -0.5f, 0.f},
		{ 0.5f,  0.5f, 0.f},
	};

	Rasterizer::Vector4f colors[]
	{
		{1.f, 0.f, 0.f},
		{0.f, 1.f, 0.f},
		{0.f, 0.f, 1.f},
		{1.f, 1.f, 1.f},
	};

	std::uint32_t indices[]
	{
		0, 1, 2, // triangle 1
		2, 1, 3, // triangle 2
	};

	Rasterizer::Matrix4x4f transform =
		Rasterizer::Matrix4x4f::Scale({ WINDOW_HEIGHT * 1.f / WINDOW_WIDTH, 1.f, 1.f })
		* Rasterizer::Matrix4x4f::Scale(0.5f)
		* Rasterizer::Matrix4x4f::RotateZX(elapsedTime)
		* Rasterizer::Matrix4x4f::RotateXY(elapsedTime * 1.61f);

	// DrawCommand initialization
	Rasterizer::DrawCommand drawCommand{};
	drawCommand.mesh = Rasterizer::cube;
	drawCommand.cullMode = Rasterizer::CullMode::Clockwise;
	drawCommand.transform = transform;

	Rasterizer::Draw(colorBuffer, viewport, drawCommand);


	// Write to the window's surface (screen)
	SDL_Rect rect{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	SDL_BlitSurface(drawSurface, &rect, SDL_GetWindowSurface(window), &rect);
	SDL_UpdateWindowSurface(window);

	return SDL_APP_CONTINUE; // Carry on with the program.
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	/* SDL will clean up the window/renderer for us. */
}

#endif // if not MY_DEBUG