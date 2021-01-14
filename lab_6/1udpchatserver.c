//Latihan 6-1 - the server can send a new message after received a message from a client

#include "arpa/inet.h"

#define SAIZTIMBAL 1024

int main(int argc, char const *argv[]) {
    int soketfd, clilen, nbytes, temp;
    char timbal[SAIZTIMBAL + 1];

    struct sockaddr_in alamatServ, alamatCli;

    // Cipta sambungan soket UDP
    soketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (soketfd < 0) {
        perror("PELAYAN: ralat untuk mencipta sambungan\n");
        exit(1);
    }

    printf("\n********************************************\n");
    printf("*****    Program Soket: CHAT SERVER    *****\n");
    printf("********************************************\n");

    // Mencipta struktur alamat untuk server
    bzero((char *)&alamatServ, sizeof(alamatServ));
    alamatServ.sin_family = AF_INET;
    alamatServ.sin_addr.s_addr = INADDR_ANY;
    alamatServ.sin_port = htons(UDP_SERVER_ECHO_PORT);

    // Memeterai alamat soket pada soketfd
    temp = bind(soketfd, (struct sockaddr *)&alamatServ, sizeof(alamatServ));
    if (temp < 0)
        perror("SERVER: ralat untuk memeterai alamat soket\n");

    printf("Menunggu sambungan...\n");

    do {
        // Kosongkan pembolehubah timbal
        bzero(timbal, sizeof(timbal));

        //menerima mesej daripada pelayan
        clilen = sizeof(alamatCli);
        nbytes = recvfrom(soketfd, timbal, SAIZTIMBAL, 0, (struct sockaddr *)&alamatCli, &clilen);
        if (nbytes < 0)
            printf("Tiada mesej  diterima daripada client\n");

        printf("Menerima mesej: %s\t\t daripada: %s\n", timbal, inet_ntoa(alamatCli.sin_addr));

        printf("Taip mesej ke CLIENT(%s) \n", inet_ntoa(alamatCli.sin_addr));

        //input mesej dari keyboard ke timbal dan hantar ke server
        fgets(timbal, sizeof(timbal), stdin);
        sendto(soketfd, timbal, SAIZTIMBAL, 0, (struct sockaddr *)&alamatCli, sizeof(alamatCli));
    } while (strcmp(timbal, "end"));

    close(soketfd);
    return 0;
}
