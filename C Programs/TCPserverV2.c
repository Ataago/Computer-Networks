//TCP server with a socket
//Workflow      socket() -> bind() -> listen() -> accept() -> read() or send()

#include<stdio.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

#include<fcntl.h>

void demo(int client_socket)
{
    char filename[256], data[2000];
    int file_discriptor;

    bzero(filename, 256);
    read(client_socket, filename, sizeof(filename));

    file_discriptor = open(filename, O_RDONLY, 0);
    read(file_discriptor, data, sizeof(data));
    send(client_socket, data, sizeof(data), 0);
}

int main()
{
    //creating a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);   //soket(domain, type, protocol)

    //specifying the address for the server
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //binding the network socket to specified IP and Port in order to listen
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    //listen connection from client
    listen(server_socket, 0);
    printf("listening to client...\n\n");
    //creating the client socket
    int client_socket;
    struct sockaddr_in client_address;
    int len = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *) &client_address, &len);

    //send data to client and then close the socket
    demo(client_socket);
    close(server_socket);

    return 0;
}