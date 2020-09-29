#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>

void insertion_sort(int arr[], int size)
{

    for (int i = 1; i < size; i++)
    {
        int j = i - 1, temp = arr[i];
        while (j >= 0 && temp < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
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
    int buf[100];
    int len = sizeof(struct sockaddr);
    int n = recvfrom(ss, buf, 100, 0, (struct sockaddr *)&tempsendaddr, &len);
    n /= sizeof(int);
    printf("Client Request:\n");
    for (int i = 0; i < n; i++)
        printf("%d  ", buf[i]);
    printf("\n");

    insertion_sort(buf, n);

    sendto(ss, &buf, sizeof(int) * n,
           0, (const struct sockaddr *)&tempsendaddr,
           len);
}
