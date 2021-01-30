#include "arpa/inet.h"

#define SAIZMAKS 512
#define MYPORT 5606

int main() {
    int soketfd, clilen, ret, bilbyte;
    char timbalterima[SAIZMAKS], timbalhantar[SAIZMAKS];

    struct sockaddr_in server, client;

    soketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (soketfd < 0) {
        printf("Ralat membuat soket\n");
        exit(1);
    }

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
        bilbyte = recvfrom(soketfd, timbalterima, sizeof(timbalterima), 0, (struct sockaddr *)&client, &clilen);

        if (bilbyte == -1)
            printf("ralat untuk menerima\n");

        else {
            timbalterima[bilbyte] = '\0';
            printf("Mesej diterima daripada Client [%s: %d]: ", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            printf("%s\n", timbalterima);
        }

        strcpy(timbalhantar, "hai");
        bilbyte = sendto(soketfd, timbalhantar, sizeof(timbalhantar), 0, (struct sockaddr *)&client, clilen);

        if (bilbyte == -1)
            printf("ralat untuk menghantar mesej\n");
    }
    close(soketfd);
    return 0;
}