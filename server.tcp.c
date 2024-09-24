#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    char *ip = "127.0.0.1";
    int port = 8080;

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    // Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket <0) {
    perror("[-]Socket error ");
    exit(1);
    }
    printf("[+] TCP Server Socket is created successfully\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Bind the ip & port to the socket
    n = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(n < 0){
    perror("[-]Bind error ");
    exit(1);
    }
    printf("[+]Bind to the port number: %d \n", port);

    // Listen to the socket
    listen(server_socket,5);  //5 clients max
    printf("[+]Listening....\n");

    // Accept the incoming connection from client
    while(1){
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        printf("[+]Client connected\n");

        bzero(buffer,1024); //just to make sure buffer dosen't hold any garbage value
        recv(client_socket,buffer,sizeof(buffer),0);
        printf("Client: %s \n",buffer);

        //server will send msg back to the client
        bzero(buffer , 1024);
        strcpy(buffer,"Hello, message recived. This is Server.");
        send(client_socket,buffer,strlen(buffer),0);
//strlen here is the size of the msg or the length od the string
        close(client_socket);
        printf("[+]Client disconnected \n\n");

    }

    return 0;
}
