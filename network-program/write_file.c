#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv)
{
   size_t capacity = 1; // capacity of the buffer for malloc
   // Length to track the buffers length itself - size_t has heavily decreased the errors
   char *buffer = malloc(capacity * sizeof(char)); // Working space of the file
   FILE *file_ptr = NULL; // 
   assert(argv[1] != NULL);
   // argv[1] assigned as the file path
   file_ptr = fopen(argv[1], "w"); // Memory leak in assignment to argv[1] - arbitrary filename
   // Takes count of the buffer as while loop
   while (fgets(buffer, sizeof(buffer), stdin) && buffer != NULL)
   {
	for(size_t len = 0; buffer[len] != '\0'; len++)
        {
                if(++len == capacity)
                {
			// realloc does the buffer 
                        buffer = realloc(buffer, (capacity *= 2) * sizeof(char*)); // memory problem 2
                }
        }
        // Loop through contents of the buffer itself
        fprintf(file_ptr, "%s", buffer);
   }
   // File stream closed and buffer memory is freed
   fclose(file_ptr);
   free(buffer);
   buffer = NULL;
   return 0;

// https://stackoverflow.com/questions/8680220/how-to-get-the-value-of-individual-bytes-of-a-variable
}
