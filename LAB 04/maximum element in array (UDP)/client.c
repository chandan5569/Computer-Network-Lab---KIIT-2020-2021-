#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int cs, bs, size;
    cs = socket(AF_INET, SOCK_DGRAM, 0);

    printf("Enter size of array: ");
    scanf("%d", &size);
    int msg[size], resp;
    printf("Enter elements of array: ");
    for (int i = 0; i < size; i++)
        scanf("%d", (msg + i));

    // setting server config
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(6011);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // sending lowercase message
    sendto(cs, msg, sizeof(int) * size, 0, (struct sockaddr *)&server, sizeof(struct sockaddr));

    // recieving uppercase message
    int len = sizeof(struct sockaddr);
    int n = recvfrom(cs, &resp, sizeof(int),
                     0, (struct sockaddr *)&server,
                     &len);
    printf("Server Response for query on greatest value in array: %d\n", resp);

    close(cs);
}
