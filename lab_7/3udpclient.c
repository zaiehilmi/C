#include <errno.h>

#include "arpa/inet.h"

#define SAIZMAKS 512
#define MYPORT 5606
#define ALAMAT "172.28.251.153"

int main() {
    int soketfd, servlen, temp, bilbyte;
    char timbalhantar[SAIZMAKS], timbalterima[SAIZMAKS];

    struct sockaddr_in server;

    soketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (soketfd < 0) {
        printf("Soket: %s\n", strerror(errno));
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(MYPORT);
    server.sin_addr.s_addr = inet_addr(ALAMAT);

    servlen = sizeof(server);

    strcpy(timbalhantar, "hello");
    bilbyte = sendto(soketfd, timbalhantar, sizeof(timbalhantar), 0, (struct sockaddr *)&server, servlen);

    if (bilbyte == -1)
        printf("Ralat Penghantaran: %s\n", strerror(errno));
    else
        printf("Mesej %s berjaya dihantar kepada [%s: %d]\n", timbalhantar, inet_ntoa(server.sin_addr), ntohs(server.sin_port));

    bilbyte = recvfrom(soketfd, timbalterima, sizeof(timbalterima), 0, (struct sockaddr *)&server, &servlen);
    if (bilbyte == -1)
        printf("Ralat penerimaan: %s\n", strerror(errno));
    else
        printf("Data daripada server: %s\n", timbalterima);

    close(soketfd);
    return 0;
}