//Latihan 8-5 - select() uses timeout of 2 minutes and 50 seconds to properly exit the program

#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>

#include "arpa/inet.h"

#define TRUE 1
#define FALSE 0
#define PORT 8888

int main(int argc, char *argv[]) {
    int opt, soketfd, clilen, soketfd_cli, client_sd[30], client_max = 30, aktiviti, i, nbaca, sd = 0, max_sd;
    char timbal[1025];
    char *mesej = "Selamat malam semua";

    fd_set readfds;
    struct timeval tv;
    struct sockaddr_in server, client;

    tv.tv_sec = 120;
    tv.tv_usec = 50000000;

    for (i = 0; i < client_max; i++)
        client_sd[i] = 0;

    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soketfd == 0) {
        perror("gagal mencipta soket\n");
        exit(EXIT_FAILURE);
    }

    opt = TRUE;
    i = setsockopt(soketfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    if (i < 0) {
        perror("gagal setsockopt\n");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    i = bind(soketfd, (struct sockaddr *)&server, sizeof(server));
    if (i < 0) {
        perror("gagal untuk mengikat\n");
        exit(EXIT_FAILURE);
    }
    printf("Mendengar di port %d\n", PORT);

    i = listen(soketfd, 5);
    if (i < 0) {
        perror("gagal untuk mendengar\n");
        exit(EXIT_FAILURE);
    }

    clilen = sizeof(client);
    puts("Menunggu untuk disambungkan...\n");

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(soketfd, &readfds);
        FD_CLR(0, &readfds);
        max_sd = soketfd;

        for (i = 0; i < client_max; i++) {
            sd = client_sd[i];

            if (sd > 0)
                FD_SET(sd, &readfds);

            if (sd > max_sd)
                max_sd = sd;
        }

        aktiviti = select(max_sd + 1, &readfds, NULL, NULL, &tv);

        if ((aktiviti < 0) && (errno != EINTR))
            printf("gagal untuk memilih\n");

        if (FD_ISSET(soketfd, &readfds)) {
            soketfd_cli = accept(soketfd, (struct sockaddr *)&client, &clilen);
            if (soketfd_cli < 0) {
                perror("gagal untuk menerima\n");
                exit(EXIT_FAILURE);
            }

            printf("Sambungan baru, soket fd: %d\n IP: %s\n Port: %d\n", soketfd_cli, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            i = send(soketfd_cli, mesej, strlen(mesej), 0);
            if (i != strlen(mesej))
                perror("penghantaran gagal\n");

            puts("Mesej berjaya dihantar\n");

            for (i = 0; i < client_max; i++) {
                //jika  posisi ialah kosong
                if (client_sd[i] == 0) {
                    client_sd[i] = soketfd_cli;
                    printf("Menambah ke dalam senarai soket: client_sd [%d]\n", i, soketfd_cli);
                    break;
                }
            }
        }
        for (i = 0; i < client_max; i++) {
            sd = client_sd[i];

            if (FD_ISSET(sd, &readfds)) {
                nbaca = read(sd, timbal, 1024);
                if (nbaca == 0) {
                    getpeername(sd, (struct sockaddr *)&client, &clilen);
                    printf("Hos menyahsambung, ip %s, port %d \n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

                    close(sd);
                    client_sd[i] = 0;
                } else {
                    timbal[nbaca] = '\0';
                    send(sd, timbal, strlen(timbal), 0);
                }
            }
        }
    }
    return 0;
}