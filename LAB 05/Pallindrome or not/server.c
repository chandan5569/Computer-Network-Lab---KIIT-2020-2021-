
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

void main()
{
    int ss, cs;

    if ((ss = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket not created!\n");
        exit(1);
    }
    printf("Server creation successful.\n");

    // setting up the server address
    struct sockaddr_in servaddr, cliaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = ntohs(8001);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(servaddr.sin_zero), '\0', 8);

    if (bind(ss, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1)
    {
        printf("Server couldn't bind.\n");
        exit(1);
    }
    printf("Server binding successful.\n");

    if (listen(ss, 1) == -1)
    {
        printf("Error while listening.\n");
        exit(1);
    }

    int size = sizeof(struct sockaddr_in);

    if ((cs = accept(ss, (struct sockaddr *)&cliaddr, &size)) == -1)
    {
        printf("Error while accepting.\n");
        exit(1);
    }
    printf("Connection established.\n");

    char req_msg[100];
    int msg_len;
    if ((msg_len = recv(cs, req_msg, 100, 0)) == -1)
    {
        printf("Message not recieved properly.\n");
        exit(1);
    }
    req_msg[msg_len] = '\0';

    // counting number of vovels
    int check = 1;
    printf("%d\n", msg_len);
    for (int i = 0; i < (int)(msg_len / 2); i++)
    {
        if (req_msg[i] != req_msg[msg_len - 1 - i])
        {
            check--;
            break;
        }
    }

    send(cs, &check, sizeof(int), 0);

    close(ss);
}
