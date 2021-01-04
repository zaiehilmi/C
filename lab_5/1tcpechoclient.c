//Latihan 5-1 - Replace the bzero function with memset function.
//baris 24 & 48, ada isu kat gets so tukar jadi fgets
#include "arpa/inet.h"

#define SAIZTIMBAL 1024

int main(int argc, char *argv[]) {
    int soketfd;
    char timbal[SAIZTIMBAL + 1];
    struct sockaddr_in alamatserver;

    //Mencipta sambungan soket TCP
    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soketfd < 0) {
        printf("Ralat untuk mencipta soket TCP");
        exit(1);
    }

    printf("\t ####################\n");
    printf("\t ##  tcpechoclient ##\n");
    printf("\t ####################\n");

    //cipta struktur alamat untuk pelayan menghantar data
    memset((char *)&alamatserver, sizeof(alamatserver), 0);

    //maklumat soket pelayan
    alamatserver.sin_family = AF_INET;
    alamatserver.sin_port = htons(TCP_SERVER_ECHO_PORT);
    inet_pton(AF_INET, argv[1], &alamatserver.sin_addr);

    //menghubungkan ke pelayan
    int temp = connect(soketfd, (struct sockaddr *)&alamatserver, sizeof(alamatserver));
    if (temp < 0) {
        printf("Tidak boleh disambungkan\n");
        exit(5);
    }

    printf("Telah disambungkan ke pelayan %s ...\n", inet_ntoa(alamatserver.sin_addr));

    do {
        printf("Masukkan mesej..\n");
        fgets(timbal, SAIZTIMBAL, stdin);
        // gets(timbal);

        //hantar mesej melalui soketfd
        send(soketfd, timbal, SAIZTIMBAL, 0);

        //kosongkan mesej daripada pelayan
        memset(timbal, sizeof(timbal), 0);

        //menerima mesej daripada pelayan
        recv(soketfd, timbal, SAIZTIMBAL, 0);
        printf("Menerima kembali [%s]\n\n", timbal);

    } while (strcmp(timbal, "\bye"));

    return 0;
}