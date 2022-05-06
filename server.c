#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int main(int argc, char *argv[])
{ 
 
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
 servaddr.sin_port = htons (atoi(argv[1]));
 
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