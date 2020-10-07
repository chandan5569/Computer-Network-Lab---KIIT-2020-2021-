#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#define BACKLOG 2 /* Number of connections in queue before being rejected*/
#define MAXDATASIZE 1000
#define STDIN 0
int main(int argc, char *argv[])
{
    int listen_fd, conn_fd, i;
    int client_fd[FD_SETSIZE];
    int max_index;
    int sin_size;
    struct sockaddr_in server; /* server's address information */
    struct sockaddr_in client; /* client's address information */
    struct sockaddr_in temp;
    if (argc != 2)
    { /* this is used because our program will need 1 argument (port) */
        printf("Usage: %s <port>\n", argv[0]);
        exit(-1);
    }

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {

        printf("socket() error\n");

        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1])); /* Remember htons() from "Conversions" section? =) */

    server.sin_addr.s_addr = INADDR_ANY; /* INADDR_ANY puts your IP address automatically */

    bzero(&(server.sin_zero), 8); /* zero the rest of the structure */

    if (bind(listen_fd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {

        printf("bind() error\n");

        exit(-1);
    }

    if (listen(listen_fd, BACKLOG) == -1)
    {

        printf("listen() error\n");

        exit(-1);
    }
    //------------------------------------------------------------------------------------------------------------------------------

    fd_set read_set, write_set, all_set;

    struct timeval timeout;
    int ret_val;

    max_index = 0;

    for (i = 0; i < FD_SETSIZE; i++)
    {

        client_fd[i] = -1;
    }

    //highest-numbered file descriptor in any of the three sets.

    int max_fd = listen_fd;

    /*initialising fd sets that are storing status of various fd*/

    FD_ZERO(&read_set);

    FD_ZERO(&write_set);

    FD_ZERO(&all_set);

    //Make the standard input socket non-blocking
    //
    fcntl(STDIN, F_SETFL, O_NONBLOCK);

    FD_SET(listen_fd, &all_set);

    while (1)
    {

        read_set = all_set;

        write_set = all_set;

        timeout.tv_sec = 100;

        timeout.tv_usec = 0;

        ret_val = select(max_fd + 1, &read_set, NULL, NULL, &timeout);

        if (ret_val == 0)
        {

            printf("\nTimeout occurred!  No data after 10 seconds.\n");
        }

        else if (ret_val == -1)
        {

            perror("select");

            exit(-1);
        }

        else if (FD_ISSET(listen_fd, &read_set))
        {

            int sin_size = sizeof(struct sockaddr_in);

            if ((conn_fd = accept(listen_fd, (struct sockaddr *)&client, &sin_size)) == -1)
            {
                perror("accept");

                exit(-1);
            }

            char temp_buf[INET_ADDRSTRLEN];

            inet_ntop(AF_INET, &(client.sin_addr), temp_buf, INET_ADDRSTRLEN);

            if (temp_buf == NULL)

                printf("inet_ntop error\n");

            else

                printf("accepted connection from client with IP Addr : %s and port Number :%u\n", temp_buf, ntohs(client.sin_port));

            if (max_index == FD_SETSIZE)

                printf("too many clients to handle\n");

            else
            {

                client_fd[max_index] = conn_fd;

                max_index++;
            }

            FD_SET(conn_fd, &all_set);

            if (conn_fd > max_fd)

                max_fd = conn_fd;

        } //end of FD_ISSET

        //_____________________________________________________________________________________________________________________________________________
        else
        { //Check the client for data

            for (i = 0; i < FD_SETSIZE; i++) //loop checks all possible sockets that are connected
            {
                sin_size = sizeof(struct sockaddr_in);

                char temp_buf[INET_ADDRSTRLEN];

                char buf[1000];
                //checks if a particular socket is ready for reading
                if (FD_ISSET(client_fd[i], &read_set))
                {

                    int numbytes;

                    numbytes = recv(client_fd[i], buf, MAXDATASIZE, 0);

                    if (numbytes > 0)
                    {

                        buf[numbytes] = '\0';

                        if (getpeername(client_fd[i], (struct sockaddr *)&temp, &sin_size) == -1)
                        {
                            printf("Peername error\n");

                            exit(-1);
                        }

                        inet_ntop(AF_INET, &(temp.sin_addr), temp_buf, INET_ADDRSTRLEN);

                        if (temp_buf == NULL)

                            printf("inet_ntop error\n");

                        else

                            printf("Message from client %s on port %u :%s", temp_buf, ntohs(temp.sin_port), buf);
                    } //
                    if (numbytes > 0)

                        if (getpeername(client_fd[i], (struct sockaddr *)&temp, &sin_size) == -1)
                        {

                            printf("Peername error\n");

                            exit(-1);
                        }

                    inet_ntop(AF_INET, &(temp.sin_addr), temp_buf, INET_ADDRSTRLEN);

                    if (temp_buf == NULL)

                        printf("inet_ntop error\n");

                    else

                        printf("My message to client %s on port %u :", temp_buf, ntohs(temp.sin_port));

                    fgets(buf, 1000, stdin);

                    send(client_fd[i], buf, strlen(buf), 0); /* send message to client */
                }                                            //
                // if (FD_ISSET(client_fd[i], &read_set))
            } // end of for
        }     //end of else
              //______________________________________________________________________________________________________________________________
    }         //end of while
}
