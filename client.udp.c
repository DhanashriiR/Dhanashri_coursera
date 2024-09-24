#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//give port number as argument
//we will listen the data or application from that port number frome which the server is broadcasting the data
int main (int argc , char **argv){
    
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    int sockfd;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size;
    int n;

    // printf("PORT: %d\n", port);

    //define socket
    sockfd = socket(AF_INET, SOCK_DGRAM,0);
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    bzero(buffer,1024);
    strcpy(buffer,"Hello, This is Server.");
    sendto(sockfd,buffer,1024,0,(struct sockaddr*)&addr,sizeof(addr));
    printf("[+] Data sent successfully\n");


    //reciving data from server
    bzero(buffer,1024);
    addr_size = sizeof(addr);
    recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&addr,&addr_size);
    printf("[+] Data recieved: %s\n",buffer);


    close(sockfd);

    return 0;

}