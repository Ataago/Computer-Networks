#include<fcntl.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<stdio.h> 

#define fifo1 "/root/fifox" 
#define fifo2 "/root/fifoy"

int main() 
{
    char filename[100],c[2000]; 
    int fd1,fd2;
    int num;

    mknod(fifo1,S_IFIFO |0777,0); 
    mknod(fifo2,S_IFIFO |0777,0); 

    printf("client online\n");
    fd1=open(fifo1,O_WRONLY,0);

    printf("enter file name\n");
    scanf("%s", filename);

    write(fd1,filename,100);
    fd2=open(fifo2,O_RDONLY);

    while((num=read(fd2,c,1999))<0);
    printf("%s",c);
    return 0;
}
