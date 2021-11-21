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


//funtion receive message from client

void func(int sockfd)

{   char buf[80];
    int n;

    for (;;) {
        bzero(buf, 80);

        read(sockfd, buf, sizeof(buf));
        printf("Message from client: %s\t Enter message : ", buf);
        bzero(buf, 80);
        n = 0;

     while ((buf[n++] = getchar()) != '\n');

       write(sockfd, buf, sizeof(buf));


        if (strncmp("exit", buf, 4) == 0) {
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

    // clear address structure
   
     bzero(&servaddr, sizeof(servaddr));


    //Prepare the sockaddr_in structure
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr = INADDR_ANY; // current host's IP address
     servaddr.sin_port = htons(8081);

    // Binding
     if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
     {  
          puts("bind failed. Error\n");
          return 1;
     }
     puts("Socket successfully binded..\n");

     

     printf("\nWELCOME TO TELNET SERVER\n============================\n\n");

     //listen
     int result;
     result=listen(sockfd,10);
     if(result ==-1){
     printf("Listen failed...\n");
     exit(0);
     }
     else
     printf("listening..\n");
     
     //Accept 
     puts("Waiting connections..."); 
     len = sizeof(cli);
     
    connfd = accept(sockfd, (struct sockaddr*)&cli, &len);

    if (connfd < 0) {
        perror("accept failed...\n");
        return 1;
    }
    else
        puts("accepting...\n");

     //

     func(connfd);

     close(sockfd);
}
     
