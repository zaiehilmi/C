//Latihan 6-2 - client able to send new message after received a message from a server

#include "arpa/inet.h"

#define SAIZTIMBAL 1024

int main(int argc, char *argv[]) {
    int soketfd, temp;
    char timbal[SAIZTIMBAL + 1];

    struct sockaddr_in alamatServer, alamatClient;

    printf("\n********************************************\n");
    printf("*****    Program Soket: CHAT CLIENT    *****\n");
    printf("********************************************\n");

    //Kosongkan pembolehubah alamatServer
    bzero((char *)&alamatServer, sizeof(alamatServer));

    //mengisi maklumat dalam struct alamatServer
    alamatServer.sin_family = AF_INET;
    alamatServer.sin_port = htons(UDP_SERVER_ECHO_PORT);
    inet_pton(AF_INET, argv[1], &alamatServer.sin_addr);

    //cipta udp soket
    temp = soketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (temp < 0)
        perror("Ralat untuk mencipta soket UDP\n");

    //mengisi maklumat struct alamatClient
    bzero((char *)&alamatClient, sizeof(alamatClient));
    alamatClient.sin_family = AF_INET;
    alamatClient.sin_addr.s_addr = INADDR_ANY;
    alamatClient.sin_port = htons(UDP_CLIENT_ECHO_PORT);

    do {
        printf("Masukkan mesej untuk dihantar ke SERVER(%s)...\n", inet_ntoa(alamatServer.sin_addr));

        //mesej diambil daripada keyboard ke timbal
        fgets(timbal, sizeof(timbal), stdin);

        //hantar mesej ke Server
        sendto(soketfd, timbal, SAIZTIMBAL, 0, (struct sockaddr *)&alamatServer, sizeof(alamatServer));

        //kosongkan timbal
        bzero(timbal, sizeof(timbal));

        //menerima mesej daripada pelayan
        recv(soketfd, timbal, SAIZTIMBAL, 0);
        printf("Menerima mesej: %s daripada %s\n\n", timbal, inet_ntoa(alamatServer.sin_addr));
    } while (strncmp(timbal, "end", 3));
    close(soketfd);

    return 0;
}
