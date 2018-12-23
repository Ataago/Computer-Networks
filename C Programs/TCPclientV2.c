//TCP client with a socket
//workflow of client    socket() -> connect() -> recv() or write()

#include<stdio.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

void demo(int client_socket)
{
    char filename[256], data[2000];

    printf("\n\nEnter the Filename: ");
    scanf("%s", filename);

    write(client_socket, filename, sizeof(filename));
    
    bzero(data, 2000);
    recv(client_socket, data, sizeof(data), 0);
    printf("Data Recieved from Server:  %s", data);
}

int main()
{
    //creating a socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);    //socket(domain, type, protocols)

    //specifying the address for the socket
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    //connect the client with server
    connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    //recieve from server and then close
    demo(client_socket);
    close(client_socket);

    return 0;
}
