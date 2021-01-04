//Latihan 5-3 - use read() and write() instead of send() and recv()

#include "arpa/inet.h"

#define SAIZTIMBAL 1024

int main(void) {
    int soketfd, soketfd_cli, clilen, temp;
    char timbal[SAIZTIMBAL];
    struct sockaddr_in alamLayan, alamLanggan;

    //mencipta soket
    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soketfd < 0) {
        printf("\nRalat untuk mencipta soket\n");
        exit(5);
    }

    printf("\t ####################\n");
    printf("\t ##  tcpechoserver ##\n");
    printf("\t ####################\n");

    //mencipta struktur alamat untuk pelayan (pelanggan boleh menghanrar data)
    bzero((char *)&alamLayan, sizeof(alamLayan));
    alamLayan.sin_family = AF_INET;
    alamLayan.sin_addr.s_addr = INADDR_ANY;
    alamLayan.sin_port = htons(TCP_SERVER_ECHO_PORT);

    //ikat soketfd dgn alamat soket
    temp = bind(soketfd, (struct sockaddr *)&alamLayan, sizeof(alamLayan));
    if (temp < 0)
        printf("TCPECHOSERVER: Ralat untuk mengikat soket");

    //menunggu sebarang permintaan sambungan drpd pelanggan
    printf("Menunggu permintaan untuk sambungan ke pelayan\nPID: %d\nPort: %d\n ...\n", getpid(), ntohs(alamLayan.sin_port));
    listen(soketfd, 5);

    //Menerima permintaan sambungan drpd pelanggan
    clilen = sizeof(alamLanggan);
    soketfd_cli = accept(soketfd, (struct sockaddr *)&alamLanggan, &clilen);
    if (soketfd_cli > 0)
        printf("Pelanggan %s (port: %d) telah menubuhkan sambungan\n\n", inet_ntoa(alamLanggan.sin_addr), ntohs(alamLanggan.sin_port));

    do {
        //menerima mesej drpd pelanggan melalui soketfd pelanggan
        recv(soketfd_cli, timbal, SAIZTIMBAL, 0);
        printf("Menerima mesej [%s]\n", timbal);

        //menghantar kembali mesej yang diterima kepada pelanggan
        send(soketfd_cli, timbal, SAIZTIMBAL, 0);
        printf("Menghantar kembali mesej [%s]\n\n", timbal);
    } while (strcmp(timbal, "/bye"));

    close(soketfd_cli);
    close(soketfd);

    return 0;
}