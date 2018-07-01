#include <stdio.h>      // Default System Calls
#include <stdlib.h>     // Needed for OS X
#include <string.h>     // Needed for Strlen
#include <sys/socket.h> // Needed for socket creating and binding
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <time.h>       // To control the timeout mechanism
#include <unistd.h>
#include <arpa/inet.h>


void connection(std::string ip, unsigned int port, Data* data)
{	
	#define EXPR_SIZE   2048
	#define BUFLEN      2048
	#define TRUE        1
	#define SERVERLEN   2048

	std::cout << "IPv4: " << ip << std::endl;

	std::cout << "Porta: " << port << std::endl;

	int fd;

    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror( "socket failed" );
    }

    struct sockaddr_in serveraddr;
    memset( &serveraddr, 0, sizeof(serveraddr) );
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons( port );
    serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );

	struct sockaddr_in clientaddr;
    socklen_t sendsize = sizeof(clientaddr);
	bzero(&clientaddr, sizeof(clientaddr));


    if ( bind(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
        perror( "bind failed" );
    }


	while (true)
	{
		char* data_string = (char*)malloc(sizeof(char) * 2048);

		int length = recvfrom(fd, data_string, sizeof(char) * 2048 , 0, (struct sockaddr *) &clientaddr, &sendsize );
        if ( length < 0 ) {
            perror( "recvfrom failed" );
            *data = Data();
            break;
        }

		data_string[length] = '\0';  // This is necessary to avoid parse errors;
        
        decode_data(data_string, data);

	}

    close( fd );

	pthread_exit(NULL);
}






#define EXPR_SIZE   1024
#define BUFLEN      512
#define TRUE        1
#define FALSE       0
#define SERVERLEN   1024


int main(int argc, char **argv)
{
    int fd;
    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {  // SOCK_SCREEN para TCP
        perror("socket failed");
        return 1;
    }

    struct sockaddr_in serveraddr;
    memset( &serveraddr, 0, sizeof(serveraddr) );
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons( 57301 );              
    inet_aton("127.0.0.1", &serveraddr.sin_addr);  // 192.168.0.1

    while ( true ) 
    {
        char* test_string = (char*) "$A123.0B1234.8C1235.2D123.3";
        if (sendto( fd, test_string, 40, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
            perror( "sendto failed" );
            break;
        }
        printf( "message sent\n" );
    }

    close( fd );
}


