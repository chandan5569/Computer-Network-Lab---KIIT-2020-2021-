#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>

char *strrev(char *str)
{
    char c, *front, *back;

    if (!str || !*str)
        return str;
    for (front = str, back = str + strlen(str) - 1; front < back; front++, back--)
    {
        c = *front;
        *front = *back;
        *back = c;
    }
    return str;
}

int main()
{
    int ss, sb;
    ss = socket(AF_INET, SOCK_DGRAM, 0);

    // setting up the server
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = ntohs(6011);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(ss, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));

    struct sockaddr_in tempsendaddr;
    char buf[100];
    int len = sizeof(struct sockaddr);
    int n = recvfrom(ss, buf, 100, 0, (struct sockaddr *)&tempsendaddr, &len);
    buf[n] = '\0';
    printf("Client Request : %s\n", buf);
    sendto(ss, (const char *)strrev(buf), strlen(buf),
           0, (const struct sockaddr *)&tempsendaddr,
           len);
}
