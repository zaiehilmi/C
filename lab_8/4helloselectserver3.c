//latihan 8-47 - the child processes in the server host terminate normally and not become zombie process

#include <errno.h>
#include <signal.h>
#include <strings.h>
#include <sys/wait.h>

#include "arpa/inet.h"

#define PORT 5000
#define SAIZ 1024

int max(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

int main(void) {
    int soketfd, soketfd_cli, udpfd, maxfd;
    char timbal[SAIZ];
    char *mesej = "Hello Client";
    const int on = 1;

    pid_t pidanak;
    fd_set readfds;
    ssize_t nbaca;
    socklen_t clilen;

    struct sockaddr_in client, server;

    //cipta soket TCP (mendengar)
    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    //ikat alamat server dengan soket
    bind(soketfd, (struct sockaddr *)&server, sizeof(server));
    listen(soketfd, 10);

    //cipta soket udp dan ikat
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(udpfd, (struct sockaddr *)&server, sizeof(server));

    //kosongkan fd
    FD_ZERO(&readfds);

    //dapatkan maxfd
    maxfd = max(soketfd, udpfd) + 1;
    for (;;) {
        //tetapkan soketfd dan udpfd dalam read set readfds
        FD_SET(soketfd, &readfds);
        FD_SET(udpfd, &readfds);

        //pilih fd yg telah bersedia
        select(maxfd, &readfds, NULL, NULL, NULL);

        //jika soket tcp boleh dibaca kemudian boleh teruskan
        if (FD_ISSET(soketfd, &readfds)) {
            clilen = sizeof(client);
            soketfd_cli = accept(soketfd, (struct sockaddr *)&client, &clilen);

            if ((pidanak = fork()) == 0) {
                close(soketfd);
                bzero(timbal, sizeof(timbal));
                printf("Mesej darpada client TCP: ");
                read(soketfd_cli, timbal, sizeof(timbal));
                puts(timbal);
                write(soketfd_cli, (const char *)mesej, sizeof(timbal));

                wait(NULL);
                close(soketfd_cli);
                exit(0);
            }
            close(soketfd_cli);
        }

        //jika menggunakan soket udp
        if (FD_ISSET(udpfd, &readfds)) {
            clilen = sizeof(client);
            bzero(timbal, sizeof(timbal));

            printf("\nMesej daripada client UDP: ");
            nbaca = recvfrom(udpfd, timbal, sizeof(timbal), 0, (struct sockaddr *)&client, &clilen);
            puts(timbal);

            sendto(udpfd, (const char *)mesej, sizeof(timbal), 0, (struct sockaddr *)&client, sizeof(client));
        }
    }
}