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

	window = SDL_CreateWindow(CLIENT_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Cvar_GetInt("width_screen"), Cvar_GetInt("height_screen"), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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

	glViewport(0, 0, 800, 600);
	gluPerspective(45.0, (double)(800) / (double)(600), 0.1f, 100.0f);

	return btrue;
}

void Render_Draw_Frame()
{
	texture_t* tex;
	int id;
	float h, w;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &id);
	tex = Texture_Get(id);
	w = 0;
	h = 0;
	if (tex != NULL)
	{
		w = tex->w / 2000.0f;
		h = tex->h / 2000.0f;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-w, h, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(w, h, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(w, -h, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-w, -h, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	SDL_GL_SwapWindow(window);
}