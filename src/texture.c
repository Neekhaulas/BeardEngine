#include "common.h"

std::map<unsigned int, texture_t*> textures;
unsigned int actualCount = 1;

void Texture_Unload_All()
{
	textures.clear();
	actualCount = 1;
}

void Texture_Draw(texture_t* tex, float w, float h, float size_w, float size_h, float x, float y, int debug)
{
	if (tex == NULL)
		return;
	glBindTexture(GL_TEXTURE_2D, tex->textureId);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, 0, 100);
	glTranslatef(x, y, 0);

	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((w)*size_w, (-h)*size_h, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((-w)*size_w, (-h)*size_h, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((-w)*size_w, (h)*size_h, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((w)*size_w, (h)*size_h, 0.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	if (debug > 0)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f((w)*size_w, (-h)*size_h, 0.0f);
		glVertex3f((-w)*size_w, (-h)*size_h, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f((-w)*size_w, (-h)*size_h, 0.0f);
		glVertex3f((-w)*size_w, (h)*size_h, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f((-w)*size_w, (h)*size_h, 0.0f);
		glVertex3f((w)*size_w, (h)*size_h, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f((w)*size_w, (h)*size_h, 0.0f);
		glVertex3f((w)*size_w, (-h)*size_h, 0.0f);
		glEnd();
	}
}

texture_t* Texture_Get(unsigned int id)
{
	if (textures[id] != NULL)
	{
		return textures[id];
	}
	return 0;
}

GLuint Texture_Load(char* nameFile)
{
	GLuint texture;
	int mode;
	SDL_Surface* surface;
	texture_t *tex;

	surface = IMG_Load(nameFile);
	if (surface == NULL)
	{
		Print_Error(1, "Cannot load surface");
		return NULL;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	mode = GL_RGB;

	if (surface->format->BytesPerPixel == 4) {
		mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	tex = new texture_t;
	tex->textureId = texture;
	tex->w = surface->w;
	tex->h = surface->h;
	tex->name = nameFile;

	textures[actualCount++] = tex;

	SDL_FreeSurface(surface);

	return texture;
}