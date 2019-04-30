#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv)
{
   int capacity = 1; // capacity of the buffer for malloc
   int len = 0; // Length to track the buffers length itself
   char *buffer = NULL;
   // Currently this will be one but will expand 
   buffer = (char*)malloc(capacity * sizeof(char));
   FILE *file_ptr = NULL; // 
   // Assigning a pointer to argv[1] for variable storage 
   assert(argv[1] != NULL);
   // argv[1] assigned as the file path
   file_ptr = fopen(argv[1], "w+");
   // Takes count of the buffer as while loop 
   while (fgets(buffer, sizeof(buffer), stdin) && buffer != NULL) 
   {
        // This will count the number of characters in the buffer, printing and reallocing memory as needed  
        for(len = 0; buffer[len] != '\n'; len++)
        {
                if(++len == capacity)
                {
                        buffer = realloc(buffer, (capacity *= 2) * sizeof(char));
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
