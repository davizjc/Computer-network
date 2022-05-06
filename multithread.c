#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 256

void *serverThread(void *input)
{
    int portNum = *(int *)input;
    char buffer[1000] = {0};
    struct sockaddr_in servaddr, cliaddr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
    {
    perror("failed to create socket");
    exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons (portNum);
    
    int rc = bind(sockfd, (const struct sockaddr *)&servaddr, 
    sizeof(servaddr));
    
    if(rc == -1)
    {
    perror("failed to bind");
    close(sockfd);
    exit(EXIT_FAILURE);
    }
    socklen_t len = 0;
    
    while (1){
    int n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
    buffer[n] = '\n';
    printf("recv from client: %s", buffer);
    }
    
    close(sockfd);
    return 0;
}

void *clientThread(void *input){

    struct sockaddr_in servaddr;
	
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr)); 
    int port; 
	char ip[256];
	printf("PLEASE INPUT TARGET PORT NUMBER: ");
	scanf("%d",&port); 
	printf("PLEASE INPUT TARGET IP: ");
	scanf("%s \n" , ip );
	
	

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr( ip );
	
	
	char hello[100000];
	while (scanf ("%[^\n]%*c", hello)){
		int len = sendto(sockfd, hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));

		if(len ==-1)
		{
		perror("failed to send");
		}
	}


	close(sockfd);
	
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 0;
    }
    int portNum = atoi(argv[1]);
    pthread_t clientTid, serverTid;
    pthread_create(&clientTid, NULL, clientThread, NULL);
    pthread_create(&serverTid, NULL, serverThread, &portNum);
    pthread_join(clientTid, NULL);
    pthread_join(serverTid, NULL);
    return 0;
}