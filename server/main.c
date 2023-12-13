#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include <unistd.h>
#include <stddef.h>

#define BUF_SIZE 1024
#define MAX_CLIENT 5


int main(void)
{

    int sockfd;
    int listener;
    struct sockaddr_in addr;
    char buffer[BUF_SIZE];
    int bytes_read;

    //prepear address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //prepear socket
    listener = socket(AF_INET, SOCK_STREAM,0);

    //bind socket
    if(bind(listener, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("Bind: ");
        exit(EXIT_FAILURE);
    }

    //listen our socket
    listen(listener,1);


    while(1)
    {
        //wait accept estabilish
        sockfd = accept(listener,NULL,NULL);
        if(sockfd < 0)
        {
            perror("Accept: ");
            exit(EXIT_FAILURE);
        }

        //if accept pass wit successful
        while(1)
        {
            //getting message
            bytes_read = recv(sockfd, buffer, BUF_SIZE, 0);
            if(bytes_read <= 0) {break;}
            //send back message
            send(sockfd, buffer, bytes_read, 0);
        }
    }

    printf("end\n");
    close(listener);
    close(sockfd);


    return 0;
}
