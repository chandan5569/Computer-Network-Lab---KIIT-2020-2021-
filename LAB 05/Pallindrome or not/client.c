
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

void main()
{
    int cs;
    cs = socket(AF_INET, SOCK_STREAM, 0);

    // putting the server address
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = ntohs(8001);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(servaddr.sin_zero), '\0', 8);

    if (connect(cs, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1)
    {
        printf("Couldn't connect to server.\n");
        exit(1);
    }
    printf("Connected to server.\n");

    char req_msg[100] = "aabbaa";
    int msg_len, check;

    send(cs, req_msg, strlen(req_msg), 0);

    if ((msg_len = recv(cs, &check, sizeof(int), 0)) == -1)
    {
        printf("Message not recieved properly.\n");
        exit(1);
    }

    if (check)
        printf("Message was palindrome.\n");
    else
        printf("Message wasn't a palindrome.\n");

    close(cs);
}
