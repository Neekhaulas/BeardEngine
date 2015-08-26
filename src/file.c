#include "common.h"

char* File_Read(char *name, char* _buffer)
{
	FILE *file;
	char *buffer;
	unsigned long fileLen;

	//Open file
	file = fopen(name, "r");
	if (!file)
	{
		Print("Unable to open file %s", name);
		return NULL;
	}

	//Get file length
	fseek(file, 0, SEEK_END);
	fileLen = ftell(file);
	rewind(file);

	//Allocate memory
	buffer = (char *)malloc(fileLen + 1);
	if (!buffer)
	{
		Print("Memory error!");
		fclose(file);
		return NULL;
	}	

	//Read file contents into buffer
	fread(buffer, fileLen, 1, file);
	buffer[fileLen - 3] = '\0';
	fclose(file);

	//Do what ever with buffer
	return buffer;
}