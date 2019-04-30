#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv)
{
   int capacity = 1; // capacity of the buffer for malloc
   int len = 0; // Length to track the buffers length itself
   //char line[100 + 1] = "";
   char *buffer = NULL;
   // Currently this will be one but will expand 
   buffer = malloc(capacity * sizeof(char));
   FILE *fp = NULL;
   // Assigning a pointer to argv[1] for variable storage 
   char *file_str = argv[1];
   assert(argv[1] != NULL);
   // argv[1] assigned as the file path
   fp = fopen(file_str, "w+");
   // Currently, line has 100 bytes; needs dynamic
   while (fgets(buffer, sizeof(buffer), stdin) != '\0' && buffer != NULL) {
        // This will count the number of characters in th  
        for(len = 0; buffer[len] != '\n'; len++)
        {
                if(++len == capacity)
                {
                        buffer = realloc(buffer, (capacity *= 2) * sizeof(char));
                }
        }
        // Loop through contents of the buffer itself
        fprintf(fp, "%s", buffer);
   }
   fclose(fp);
   return 0;

// https://stackoverflow.com/questions/8680220/how-to-get-the-value-of-individual-bytes-of-a-variable
}
