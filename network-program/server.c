#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

// Socket is created for the server to listen for a potential client
// file stream opened to recieve a file 
int main(int argc, char *argv[])
{
	int listen_file_descriptor = 0;
	int connection_file_descriptor = 0;
	struct sockaddr_in server_address;
	char *send_buff = malloc(100 * sizeof(char));
	int num_recieved = 0;
	return 0;
}
