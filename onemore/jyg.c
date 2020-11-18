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
#include <fcntl.h>
#include <signal.h>
#include <sys/signalfd.h>

int sfd;
int cfd;

void loosecanon(int signum) {
    close(cfd);
    close(sfd);
    printf(" termination here\n");
    exit(EXIT_SUCCESS);
}

int main(int argc , char *argv[])
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = loosecanon;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGHUP, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    struct sockaddr_in addr = { AF_INET , htons( 8888 ) /* btc port */ , htonl(INADDR_LOOPBACK) };;
    int down_flag = 0;
    int result = 0;
    int ret = 0;
    bool c = !false;
    int bc = 1024;    

    sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sfd < 0) {
        perror("Create server socket error: %s\n");
        return 0;
    }
    setsockopt(sfd, IPPROTO_TCP, TCP_NODELAY, (char *)&c, sizeof(c));
    setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, (char *)&c, sizeof(c));
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&c, sizeof(c));
    setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, (char *)&c, sizeof(c));
    setsockopt(sfd, SOL_SOCKET, SO_SNDBUF, (int *)&bc, sizeof(bc));
    setsockopt(sfd, SOL_SOCKET, SO_RCVBUF, (int *)&bc, sizeof(bc));
    
    /* Bind socket to loopback address */
    if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1) {
        perror("Bind server socket failed");
        goto _exit;
    }
    setsockopt(sfd, IPPROTO_TCP, TCP_NODELAY, (char *)&c, sizeof(c));

    if (listen(sfd, 128) == -1) {
        perror("Listen failed");
        goto _exit;
    }

    ssize_t num_rd = 0;
    enum { buf_size = 1025 };
    char buf[buf_size] = {0};
    char name[buf_size] = {0};
    sigset_t sig;
    sigset_t *xsig = &sig;
    struct pollfd pfd[2] = {{0}};
    int nready;
    sigemptyset(xsig);
    sigaddset(xsig, SIGINT);
    sigaddset(xsig, SIGTERM);
    sigaddset(xsig, SIGHUP);
    pfd[1].fd = signalfd(-1 ,xsig ,SFD_NONBLOCK);
    pfd[1].events = POLLIN;
 //   sigprocmask(SIG_BLOCK, xsig, NULL);
   
    for (;;)
    {
        bool name_again = false;
        bool eof_flag = false;

        printf("Waiting to accept a connection...\n");
        cfd = accept(sfd, NULL, NULL);
        printf("Accepted socket fd = %d\n", cfd);
        if(cfd == -1)
        {
            perror("looks like SIGTERM");
            goto _exit;
        } 
        result = 0;
        pfd[0].fd = cfd;
//      pfd[0].fd = sfd;
        pfd[0].events = POLLIN;

        memset(buf, 0, sizeof(buf));
        nready = poll(pfd, 2, 15 * 1000);
        if (pfd[1].revents & POLLIN) {
            printf("termination signal\n");            
            goto _exit;
        }
        num_rd = read(cfd, buf, sizeof(buf) - 1);
        if (!strncmp(buf, "DOWN\xF7", 20)) {
            close(cfd);
            printf("shutdown..\n");            
            goto _exit;
        }        
        memset(name, 0, sizeof(name));
        strcpy(name, buf);
        memset(buf, 0, sizeof(buf));        
        nready = poll(pfd, 2, 15 * 1000);
        if (pfd[1].revents & POLLIN) {
            printf("termination signal\n");            
            goto _exit;
        }        
        num_rd = read(cfd, buf, sizeof(buf) - 1);
        printf("Read data: %s\n", buf);
        if (!strncmp(buf, "DOWN\xF7", 20)) {
            close(cfd);
            printf("shutdown..\n");            
            goto _exit;
        }
        if (!strncmp(buf, "NAME\xF7", 20)) {
            printf("so filename received is: %s\n", name);
        }
        else {
            close(cfd);
            perror("no-name");
            continue;
        }
        int wx = open(name ,O_WRONLY|O_CREAT|O_TRUNC ,0777);
        if(wx == -1) {
            perror("Write error , file i/o\n");
            goto _exit;
        }
        while (!false) {
            memset(buf, 0, sizeof(buf));
            nready = poll(pfd, 2, 15 * 1000);
            if (pfd[1].revents & POLLIN) {
                printf("termination signal\n");            
                goto _exit;
            }            
            num_rd = read(cfd, buf, sizeof(buf) - 1);
            if (num_rd <= 0) break;
            /* Handle commands */
            if (!strncmp(buf, "DOWN\xF7", 20)) {
                down_flag = 1;
                printf("Read data: %s\n", buf);
                break;
            }
            if (!strncmp(buf, "END\xF7", 20)) {
                printf("Read data: %s\n", buf);
                break;
            }
            if (!strncmp(buf, "NAME\xF7", 20)) {
                name_again = !false;
                printf("Read data: %s\n", buf);
                break;
            }
            if (!strncmp(buf, "EOF\xF7", 20)) {
                printf("Read data: %s\n", buf);
                eof_flag = !false;
                continue;
            }
            if (eof_flag) {
                sigprocmask(SIG_BLOCK, xsig, NULL);
                ret = write(wx, buf, strlen(buf));
                sigprocmask(SIG_UNBLOCK, xsig, NULL);
                if (-1 == ret) {
                    perror("Write error , file i/o\n"); //то что файл открыт я не вижу проблем
                    goto _exit;
                }
                continue;
            }
            sigprocmask(SIG_BLOCK, xsig, NULL);
            ret = write(wx, buf, sizeof(buf) - 1);
            sigprocmask(SIG_UNBLOCK, xsig, NULL);
            if (-1 == ret) {
                perror("Write error , file i/o\n");
                goto _exit;
            }         
        }
        if (-1 == num_rd) {
            perror("Read error");
        }
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "all right");
        pfd[0].events = POLLOUT;
        nready = poll(pfd, 2, 15 * 1000);
        if (pfd[1].revents & POLLIN) {
            printf("termination signal\n");            
            goto _exit;
        }
        ret = write(cfd, buf, sizeof(buf) - 1);
        if (-1 == ret) {
            perror("Write error\n");
            goto _exit;
        }
        close(cfd);
        close(wx); 
        /* Quit on DOWN command */
        if (down_flag) {
            break;
        }
    }
_exit:
    close(sfd);
    return 0;
}