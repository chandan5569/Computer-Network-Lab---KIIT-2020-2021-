#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int ss, sb;
    ss = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = ntohs(6011);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(ss, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
    struct sockaddr_in tempsendaddr;
    char buf[100];
    int len = sizeof(struct sockaddr);
    recvfrom(ss, buf, 100, 0, (struct sockaddr *)&tempsendaddr, &len);
    printf("Client Request : %s", buf);

    char *msg = "Hello from the server side \n";
    sendto(ss, (const char *)msg, strlen(msg),
           0, (const struct sockaddr *)&tempsendaddr,
           len);
}
