#include<stdio.h>
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<fcntl.h>

int main(int argc,char **argv) 
{
    int sockfd, newsockfd, portno = 7000, clienlen; 
    char filename[256], c[2000];
    struct sockaddr_in serv_addr, clin_addr;
    int fd;

    printf("Enter the port number: \n"); 
    scanf("%d",&portno);

    sockfd = socket(AF_INET,SOCK_STREAM,0); 
    bzero((char*)&serv_addr,sizeof(serv_addr)); 
    serv_addr.sin_family=AF_INET; 
    serv_addr.sin_port=htons(portno);
    serv_addr.sin_addr.s_addr=INADDR_ANY; 

    bind(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr));
    listen(sockfd,5);

    printf("server waiting for client\n");
    clienlen = sizeof(clin_addr);
    newsockfd = accept(sockfd,(struct sockaddr *)&serv_addr, &clienlen);
    
    bzero(filename,256); 
    read(newsockfd, filename, 255);
    fd = open(filename, O_RDONLY, 0); 
    read(fd, c, 1999); 
    send(newsockfd, c, 1999, 0); 
    close(newsockfd);
    return 0; 
}