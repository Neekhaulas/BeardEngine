#include "common.h"

static SDL_Window *window = NULL;

void Render_Init()
{
	Print("Render initializing");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Print_Error(1, "Can't initialize SDL Video");
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow(CLIENT_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window)
	{
		Print_Error(1, "Can't create SDL window");
		exit(1);
	}

	if (SDL_GL_CreateContext(window) == NULL)
	{
		Print_Error(1, "Error while creating OpenGL context");
		exit(1);
	}

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Print_Error(1, "Error while initilizing GLEW");
		exit(1);
	}
}