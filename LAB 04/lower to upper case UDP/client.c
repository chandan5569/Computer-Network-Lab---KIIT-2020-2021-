#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int cs, bs;
    cs = socket(AF_INET, SOCK_DGRAM, 0);

    char msg[] = "cn lab good.\n", uc_msg[1000];

    // setting server config
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(6011);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // sending lowercase message
    sendto(cs, msg, sizeof(msg), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));

    // recieving uppercase message
    int len = sizeof(struct sockaddr);
    int n = recvfrom(cs, (char *)uc_msg, 1000,
                     0, (struct sockaddr *)&server,
                     &len);
    uc_msg[n] = '\0';
    printf("Server Response : %s", uc_msg);

    close(cs);
}
