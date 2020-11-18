#include <stdio.h>
#include <stddef.h>
#include <sys/socket.h>    //socket
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <netinet/tcp.h>
#include <string.h>
#include <poll.h>
#include <libgen.h>

int main(int argc , char *argv[])
{
    struct sockaddr_in addr = { AF_INET , htons( 8888 ) /* btc port */ , htonl(INADDR_LOOPBACK) };;
    int down_flag = 0;
    int result = 0;
    int ret = 0;
    bool c = !false;
    int bc = 1024;
    enum { buf_size = 1025 };
    char buf[buf_size] = {0};
    char buf2[buf_size] = {0};

    int data_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(data_socket, SOL_SOCKET, SO_KEEPALIVE, (char *)&c, sizeof(c));
    setsockopt(data_socket, IPPROTO_TCP, TCP_NODELAY, (char *)&c, sizeof(c));
    setsockopt(data_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&c, sizeof(c));
    setsockopt(data_socket, SOL_SOCKET, SO_REUSEPORT, (char *)&c, sizeof(c));
    setsockopt(data_socket, SOL_SOCKET, SO_SNDBUF, (int *)&bc, sizeof(bc));
    setsockopt(data_socket, SOL_SOCKET, SO_RCVBUF, (int *)&bc, sizeof(bc));

    ret = connect(data_socket, (const struct sockaddr *) &addr, sizeof(addr));
    if (-1 == ret) {
        perror("Connect error");
        exit(EXIT_FAILURE);
    }
    setsockopt(data_socket, IPPROTO_TCP, TCP_NODELAY, (char *)&c, sizeof(c));    /* Send arguments */
    setsockopt(data_socket, SOL_SOCKET, SO_KEEPALIVE, (char *)&c, sizeof(c));

    struct pollfd pfd[1];
    int nready;
    pfd[0].fd = data_socket;
    pfd[0].events = POLLOUT;
    if (argc == 2 && strncmp(argv[1] , "SHUTDOWN?" , 20) == 0) {
        strcpy(buf, "DOWN\xF7");
        nready = poll(pfd, 1, 15 * 1000);
        ret = write(data_socket, buf, sizeof(buf) - 1);
        printf("write %s to socket, ret = %d\n", buf, ret);
        close(data_socket);
        exit(EXIT_SUCCESS);
    }

    FILE *w;
    if ( argc != 2 || (w = fopen(argv[1] , "r+")) == NULL) {
        perror("no bowler");
        exit(EXIT_FAILURE);
    }
    strcpy(buf, basename(argv[1]));
    nready = poll(pfd, 1, 15 * 1000);
    ret = write(data_socket, buf , sizeof(buf) - 1);
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "NAME\xF7");
    nready = poll(pfd, 1, 15 * 1000);
    ret = write(data_socket, buf, sizeof(buf) - 1);

    while (!false)
    {

        memset(buf, 0, sizeof(buf));
        fread(buf , 1 , sizeof(buf) - 1 , w);
        if (feof(w)) {
            strcpy(buf2 , "EOF\xF7");
            nready = poll(pfd, 1, 15 * 1000);
            ret = write(data_socket, buf2 , sizeof(buf2) - 1);

            nready = poll(pfd, 1, 15 * 1000);
            ret = write(data_socket, buf , sizeof(buf) - 1);
            break;
        }

        nready = poll(pfd, 1, 15 * 1000);
        // if((pfd[0].revents & (POLLOUT|POLLHUP))) printf("tray \n" );
        ret = write(data_socket, buf , sizeof(buf) - 1);
        if (-1 == ret) {
            perror("Write error");
            break;
        }
    }

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "END\xF7");
    nready = poll(pfd, 1, 15 * 1000);
    ret = write(data_socket, buf, sizeof(buf) - 1);
    printf("write %s to socket, ret = %d\n", buf, ret);
    if (-1 == ret) {
        perror("Write to socket error");
        exit(EXIT_FAILURE);
    }
    /* Read the result */
    memset(buf, 0, sizeof(buf));
    pfd[0].events = POLLIN;
    nready = poll(pfd, 1, 15 * 1000);
    ret = read(data_socket, buf, sizeof(buf) - 1);
    if (-1 == ret) {
        perror("Read from client socket error");
        fclose(w);
        exit(EXIT_FAILURE);
    }
    printf("%s\n", buf);
    fclose(w);
    close(data_socket);
    exit(EXIT_SUCCESS);
}