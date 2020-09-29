
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

    // send
    int arr_size;
    printf("Enter the size of array: ");
    scanf("%d", &arr_size);

    int req_msg[arr_size];
    printf("Enter the array: ");
    for (int i = 0; i < arr_size; i++)
        scanf("%d", (req_msg + i));

    send(cs, req_msg, sizeof(int) * arr_size, 0);

    // recieve
    int msg_len, sum;
    if ((msg_len = recv(cs, &sum, sizeof(int), 0)) == -1)
    {
        printf("Message not recieved properly.\n");
        exit(1);
    }

    printf("Sum of elements is: %d.\n", sum);

    close(cs);
}
