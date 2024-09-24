#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//give port number as argument
//we will send data from server to that port number
int main (int argc , char **argv){
    
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_size;
    int n;

    printf("IP: %s\n", ip);
    printf("PORT: %d\n", port);

    //define socket
    sockfd = socket(AF_INET, SOCK_DGRAM,0);
    if(sockfd < 0){
        perror("[-] Socket error");
        exit(1);
    }

    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
    if(n<0){
        perror("[-] Bind error");
        exit(1);
    }

    //In UDP we do not estabilish any connetion to the client, we directly send the data
    bzero(buffer,1024);
    addr_size = sizeof(client_addr);
    recvfrom(sockfd,buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+]Data received: %s\n",buffer);

    //send data back to client
    bzero(buffer,1024);
    strcpy(buffer,"Welcome to Server. This is UDP Server.");
    sendto(sockfd,buffer,1024,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
    printf("[+]Data sent : %s\n",buffer);


    return 0;
}