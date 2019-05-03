#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv)
{
   size_t capacity = 1; // capacity of the buffer for malloc
   char *buffer = malloc((int)capacity * sizeof(char*)); // Working space of the file
   //char *file_name = argv[1];
   FILE *file_ptr = NULL; 
   assert(argv[1] != NULL);
   file_ptr = fopen(argv[1], "a");
   // Takes count of the buffer as while loop
   while (fgets(buffer, sizeof(buffer), stdin) && buffer != NULL)
   {
        for(size_t len = 0; len <= *buffer; len++)
        {
                if(len == (size_t)capacity)
                {
                        buffer = realloc(buffer, (capacity *= 2) * sizeof(char*));
                }
        }
        fprintf(file_ptr, "%s", buffer);
   }
   // File stream closed and buffer memory is freed
   fclose(file_ptr);
   free(buffer);
   buffer = NULL;
   file_ptr = NULL;
   return 0;

// https://stackoverflow.com/questions/8680220/how-to-get-the-value-of-individual-bytes-of-a-variable
}
