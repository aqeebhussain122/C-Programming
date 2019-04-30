#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv)
{
   size_t capacity = 1; // capacity of the buffer for malloc
   size_t len = 0; // Length to track the buffers length itself - size_t has heavily decreased the errors
   char *buffer = NULL; // Working memory space
   // char **strs 	= NULL; // String pointers to attach 
   // Currently this will be one but will expand 
   buffer = malloc(capacity * sizeof(char));
   FILE *file_ptr = NULL; // 
   // Assigning a pointer to argv[1] for variable storage 
   //assert(argv[1] != NULL);
   // argv[1] assigned as the file path
   file_ptr = fopen(argv[1], "w"); // Memory leak in assignment to argv[1] - arbitrary filename
   // Takes count of the buffer as while loop 
   while (fgets(buffer, sizeof(buffer), stdin) && buffer != NULL) 
   {
	
	// 
        for(size_t i = 0; buffer[i] != '\0' && buffer[i] != EOF; i++)
        {
		buffer[i] = len;
                if(len == capacity)
                {
                        buffer = realloc(buffer, (capacity *= 2) * sizeof(char)); // memory problem 2
			// Might cause an error
			free(buffer);
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
