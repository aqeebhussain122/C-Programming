#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    // Pointer based malloc in sendBuff variable
    char sendBuff[1025];
    time_t ticks; 

    // Enable a TCP socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Program binded to port 5000 by default
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    // Maximum number of listening connections
    listen(listenfd, 1); 

    // While(1) should be changed to 
    while(1)
    {
	// Socket is accepted from the client and is prepared with the template values
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        ticks = time(NULL);
	// Print procedure happens on the terminal
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
	// Connection file descriptor sends off the buffer data to the client 
        write(connfd, sendBuff, strlen(sendBuff)); 
	// Connection is closed off to prevent corruption
        close(connfd);
        sleep(1);
     }
	return 0;
}
