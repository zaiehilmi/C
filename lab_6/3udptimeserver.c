//Latihan 6-3 - transport protocol used is UDP instead of TCP

#include <time.h>

#include "arpa/inet.h"

#define SAIZTIMBAL 1024

int main(void) {
    int soketfd, soketfdCli, clilen, temp;
    char timbal[SAIZTIMBAL + 1];

    time_t nilaiMasa;
    struct sockaddr_in alamatServer, alamatClient;

    /* Creating UCP socket connection */
    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soketfd < 0) {
        printf("Ralat pada soket\n");
        exit(1);
    }

    system("clear");
    printf("\t###############################\n");
    printf("\t# Socket Program: TIME SERVER #\n");
    printf("\t###############################\n");

    /* Creating address structure for server (so client can send data) */
    bzero((char *)&alamatServer, sizeof(alamatServer));

    alamatServer.sin_family = AF_INET;
    alamatServer.sin_addr.s_addr = INADDR_ANY;
    alamatServer.sin_port = htons(UDP_SERVER_TIME_PORT);

    // Bind sockfd with socket address
    temp = bind(soketfd, (struct sockaddr *)&alamatServer, sizeof(alamatServer));
    if (temp < 0) {
        printf("Ralat untuk mengikat soket\n");
        exit(2);
    }

    // Waiting for any connection request from client
    printf("Menunggu sambungan...[bind]\n\n");

    listen(soketfd, 5);

    // Accept a connection request from a client
    clilen = sizeof(alamatClient);
    soketfdCli = accept(soketfd, (struct sockaddr *)&alamatClient, &clilen);
    if (soketfdCli > 0) {
        printf("Client %d telah menubuhkan sambungan..\n\n", ntohs(alamatClient.sin_port));

        //receiving message from the client via cli_sockfd
        recv(soketfdCli, timbal, SAIZTIMBAL, 0);
        printf("Bersedia untuk menerima transaksi...\n");

        //capture the local time from server
        time(&nilaiMasa);

        printf("MASA di SERVER sekarang ialah %s\n", ctime(&nilaiMasa));

        //copying the captured time into buffer
        strcpy(timbal, ctime(&nilaiMasa));

        //send the captured time to the client
        send(soketfdCli, timbal, SAIZTIMBAL, 0);

        //printf("Sent %s\n", buffer);

        close(soketfdCli);
        close(soketfd);
    }
    //e-if(cli_sockfd)
    return 0;
}