#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int cs, bs;
    cs = socket(AF_INET, SOCK_DGRAM, 0);

    // struct sockaddr_in x;
    // x.sin_family = AF_INET;
    // x.sin_port = ntohs(6009);
    // x.sin_addr.s_addr = inet_addr("127.0.0.1");

    // bs = bind(cs, (struct sockaddr *)&x, sizeof(x));
    char msg[] = "Hello from the client side.\n", msg1[1000];

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(6011);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(cs, msg, sizeof(msg), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));
    int len = sizeof(struct sockaddr);
    int n = recvfrom(cs, (char *)msg1, 1000,
                     0, (struct sockaddr *)&server,
                     &len);
    msg1[n] = '\0';
    printf("Server Response : %s", msg1);

    close(cs);
}
