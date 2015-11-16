#include "common.h"

static SDL_Window *window = NULL;
GLuint texture;

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

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		Print_Error(1, "Unable to set VSync");
	}

	if (!Render_InitGL())
	{
		Print_Error(1, "Unable to initialize OpenGL");
		exit(1);
	}
}

beboolean Render_InitGL()
{
	bool success = true;
    GLenum error = GL_NO_ERROR;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }

	SDL_Surface* Surface = IMG_Load("data/textures/bg_layer4.png");
	if (Surface == NULL)
	{
		Print_Error(1, "Cannot load surface");
		return bfalse;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int Mode = GL_RGB;

	if (Surface->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return btrue;
}

void Render_Draw_Frame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 800, 600);
	gluPerspective(45.0, (double)(800) / (double)(600), 0.1f, 100.0f);

	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.7f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.7f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	SDL_GL_SwapWindow(window);
}