#include "common.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <io.h>

file_t* File_Read(char *name)
{
	file_t* f;
	char *buffer;
	FILE *file;
	int size, read_size;

	file = fopen(name, "rb");
	if (!file)
	{
		Print_Error(0, "Cannont open file %s", name);
		return NULL;
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);

	buffer = malloc(sizeof(char) * (size + 1));
	read_size = fread(buffer, sizeof(char), size, file);
	buffer[size] = '\0';

	if (size != read_size)
	{
		free(buffer);
		buffer = NULL;
		Print_Error(1, "Error while reading file");
	}

	fclose(file);
	f = malloc(sizeof(file_t));
	f->data = buffer;
	f->max_size = 128*1024;
	f->current_size = size;
	return f;
}