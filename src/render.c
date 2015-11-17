#include "common.h"

static SDL_Window *window = NULL;
GLuint texture1, texture2;

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

	Print("Test %d %d %d", texture1, texture2, texture1);

	glViewport(0, 0, 800, 600);
	gluPerspective(45.0, (double)(800) / (double)(600), 0.1f, 100.0f);

	return btrue;
}

GLfloat     rtri;

void Render_Draw_Frame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(rtri, 1.0f, 1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, texture1);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	SDL_GL_SwapWindow(window);

	rtri += 1.0f;
}