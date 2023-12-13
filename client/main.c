#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>



void Menu(void)
{
    printf("1 - Registration\n 2 - Login\n 3 - Disconnect\n");
}



int main(void)
{
    int choose = 0;
    char msg[]="our message\n";
    const char REG[] = "re";
    const char LOG[] = "log";

    char buffer[sizeof(msg)];
    

    char Login[10];
    char Password[10];


    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        perror("socket: ");
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    printf("Enter 1 - coonect to server: ");
    scanf("%d", &choose);

    if(choose == 1)
    {
        if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("connect: ");
            exit(EXIT_FAILURE);
        }
        printf("connection successful\n");

        Menu();
        scanf("%d", &choose);
        if(choose == 1)
        {
            printf("sending request on registration...\n");
            send(sockfd, REG, sizeof(REG), 0);

            /*printf("You Login: ");
            scanf("%s", &Login);
            printf("You Password: ");
            scanf("%s", &Password);
            printf("data got\n");
            send(sockfd, Login, sizeof(Login), 0);*/
        }

    }
    else
    {
        printf("Unknown operration\n");
        exit(EXIT_FAILURE);
    }

    

    

    printf("%s \n", buffer);
    close(sockfd);

    return 0;
}
