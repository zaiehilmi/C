#include "arpa/inet.h"

#define SAIZMAKS 512
#define MYPORT 5606

int main() {
    int soketfd, clilen, ret, bilbyte;
    // char timbalterima[SAIZMAKS], timbalhantar[SAIZMAKS];
    char timbal[SAIZMAKS];

    struct sockaddr_in server, client;

    soketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (soketfd < 0) {
        printf("Ralat membuat soket\n");
        exit(1);
    }

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(MYPORT);
    server.sin_addr.s_addr = INADDR_ANY;

    ret = bind(soketfd, (struct sockaddr *)&server, sizeof(server));
    if (ret == -1) {
        printf("gagal membuat sambungan ke server\n");
        exit(2);
    }

    while (1) {
        printf("Server UDP menunggu Client\n");
        clilen = sizeof(client);
        bilbyte = recvfrom(soketfd, timbal, sizeof(timbal), 0, (struct sockaddr *)&client, &clilen);

        if (bilbyte == -1)
            printf("ralat untuk menerima\n");

        else {
            // timbal[bilbyte] = '\0';
            printf("Mesej diterima daripada Client [%s: %d]: ", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            printf("%s\n", timbal);
        }

        bzero(timbal, sizeof(timbal));
        strcpy(timbal, "hai");
        bilbyte = sendto(soketfd, timbal, sizeof(timbal), 0, (struct sockaddr *)&client, clilen);

        if (bilbyte == -1)
            printf("ralat untuk menghantar mesej\n");
    }
    close(soketfd);
    return 0;
}