#include "common.h"

std::map<char*, texture_t*> textures;

texture_t* Texture_Get(char* textureName)
{
	if (textures[textureName] != NULL)
	{
		return textures[textureName];
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

	textures[nameFile] = tex;

	SDL_FreeSurface(surface);


	return texture;
}