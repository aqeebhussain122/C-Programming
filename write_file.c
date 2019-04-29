#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/*
 * Open the file and write as many lines as you like to it
 */
int main(int argc, char *argv[])
{
	int chr = 0;
	int write;
	// Capacity used to track buffer limit
	int capacity = 1;
	// Length of the buffer
	int len = 0;
	// Characters in the buffer
	FILE *file_ptr = NULL;
	file_ptr = fopen("file", "wb");
	// File pointer used opening the file
	// int lines; - Changed into character buffer space for characters to be stored
	char *buffer = NULL; // Good practice to prevent unintented access to memory spaces
	char **strs = NULL;
	strs = &buffer;
	// Start off with 1 byte and dynamically realloc later 
	buffer = malloc(capacity * sizeof(char));
	/*
	while (fgets(buffer, sizeof(buffer), stdin) != NULL && !feof(stdin))
	{
		//buffer[len] = len;
		if(*buffer == capacity)
		{
			buffer = realloc(buffer, (capacity *= 2) * sizeof(char));
		}
		file_ptr = fopen("file", "w");
		strs = &buffer;
		printf("%s", *strs);
		// File pointer does not seem to match up 
	        for (int i = 0; (write = getc(file_ptr)) != EOF && i < capacity; buffer[capacity++] = write);
		// Bytes written check
		//size_t count = fwrite(buffer, 1, strlen(buffer), file_ptr);
		//printf("\n%zu bytes written", count);

		fprintf(file_ptr, "%s\n", buffer);
		fflush(file_ptr);
	}
	*/
	
	//fprintf(file_ptr, "%s", *strs); - 
	while((chr = fgetc(stdin)) != '\0' && !feof(stdin))
	{
		buffer[len] = chr;
		if(++len == capacity) 
		{
			buffer = realloc(buffer, (capacity *= 2) * sizeof(char));
		}
		strs = &buffer;
		printf("%s", *strs);
		fprintf(file_ptr, "%s\n", *strs);
                //fflush(file_ptr);
	}
	
	if(buffer == NULL)
	{
		printf("Couldn't allocate memory");
		return 1;
	}
	else 
	{
		memset(buffer, 0, len * sizeof(buffer[0]));
	}
	
	fclose(file_ptr);
	free(buffer);
	return 0;
}
// https://stackoverflow.com/questions/41407318/warning-passing-argument-2-of-fopen-makes-pointer-from-integer-without-a-cast
