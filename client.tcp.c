#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    char *ip = "127.0.0.1";
    int port = 8080;

    int client_socket;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    // Create TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket <0) {
    perror("[-]Socket error ");
    exit(1);
    }
    printf("[+] TCP Server Socket is created successfully\n");

   // Setup address structure
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET; // IPv4
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    //connecting to the server
    connect(client_socket,(struct sockaddr*)&addr, sizeof(addr));
    printf("[+]Connected to the server\n");

    //just to make sure buffer dosen't hold any garbage value
    bzero(buffer,1024);
    strcpy(buffer,"Hello, This is Client.");
    printf("Client: %s \n",buffer);
    send(client_socket,buffer,strlen(buffer),0);

    bzero(buffer,1024);
    recv(client_socket, buffer, sizeof(buffer) ,0);
    printf("Server: %s \n",buffer);

    close(client_socket);
    printf("disconnected from the server. \n");

    return 0;
}
