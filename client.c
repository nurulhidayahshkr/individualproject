#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <arpa/inet.h>

void func(int sockfd)

{     char buf[80];
     int n;
     for (;;) {
        bzero(buf, sizeof(buf));
        printf("Enter message : ");
        n = 0;
        while ((buf[n++] = getchar()) != '\n')
            ;
        write(sockfd, buf, sizeof(buf));
        bzero(buf, sizeof(buf));
        read(sockfd, buf, sizeof(buf));

        printf("Message from Server :%s", buf);

        if ((strncmp("exit",buf, 4)) == 0) {
            printf("disconnected...\n");
            break;
           }
               }

}
int main(int argc, char *argv[])
{


   //create socket
   int sockfd,connfd, len;
   struct sockaddr_in servaddr, cli;

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Could not create socket\n");
        return 1;
    }
    else
        printf("Socket created\n");

 bzero(&servaddr, sizeof(servaddr));

   //Prepare the sockaddr_in structure
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr= inet_addr("192.168.0.107"); // current host's IP address
     servaddr.sin_port = htons(8081);


    printf("\nWELCOME TO TELNET CLIENT 3\n==========================\n\n");



     //connect
     if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect failed. Error\n");
        return 1;
    }
    else
        puts("connected to server\n");

     //

   func(sockfd);

    close(sockfd);
}


