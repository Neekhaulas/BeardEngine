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

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
	return btrue;
}

void Render_Draw_Frame()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3ub(255, 0, 0);    glVertex2d(-0.75, -0.75);
	glColor3ub(0, 255, 0);    glVertex2d(0, 0.75);
	glColor3ub(0, 0, 255);    glVertex2d(0.75, -0.75);
	glEnd();

	glFlush();

	SDL_GL_SwapWindow(window);
}