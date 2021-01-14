//Latihan 6-4 transport protocol used is UDP instead of TCP

#include "arpa/inet.h"
#define SAIZTIMBAL 1024

int main(int argc, char *argv[]) {
    int soketfd, temp;
    char buffer[SAIZTIMBAL + 1];
    struct sockaddr_in alamatServer;

    /* Creating UDP socket connection */
    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soketfd < 0) {
        printf("Ralat pada soket\n");
        exit(1);
    }

    //system("clear");
    printf("\t###############################\n");
    printf("\t# Socket Program: TIME CLIENT #\n");
    printf("\t###############################\n");

    /* create address structure for server (so client can send data) */
    bzero((char *)&alamatServer, sizeof(alamatServer));

    alamatServer.sin_family = AF_INET;
    alamatServer.sin_port = htons(UDP_SERVER_TIME_PORT);
    inet_pton(AF_INET, argv[1], &alamatServer.sin_addr);

    //connect to tcptimeserver
    temp = connect(soketfd, (struct sockaddr *)&alamatServer, sizeof(alamatServer));
    if (temp < 0) {
        printf("Ralat untuk disambungkan\n");
        exit(2);
    }

    printf("Sambungan telah terbina dengan SERVER %s\n", inet_ntoa(alamatServer.sin_addr));
    printf("Masa pada SERVER %s?\n", inet_ntoa(alamatServer.sin_addr));

    //send the message via sockfd
    send(soketfd, buffer, SAIZTIMBAL, 0);

    //emptied the buffer
    bzero(buffer, sizeof(buffer));

    //receive message from the server via sockfd
    recv(soketfd, buffer, SAIZTIMBAL, 0);
    printf("Masa diterima daripada SERVER %s ialah: %s\n", inet_ntoa(alamatServer.sin_addr), buffer);

    close(soketfd);

    return 0;
}
