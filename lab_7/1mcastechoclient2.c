// Latihan 7-1 - the input is the local time of client host to be send and echoed by the server

#include <errno.h>
#include <time.h>

#include "arpa/inet.h"

#define MCAST_ECHOSERVER_PORT 49000
#define MAX_MSG 100

int main(int argc, char *argv[]) {
    int soketfd, temp, i;
    char timbal[1024];
    unsigned char ttl = 1;

    time_t masa;
    struct sockaddr_in client, server;

    // if (argc < 3) {
    //     printf("Usage : %s <mgroup> <data1> <data2> ... \n", argv[0]);
    //     exit(1);
    // }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(MCAST_ECHOSERVER_PORT);

    /* check if dest address is multicast */
    if (!IN_MULTICAST(ntohl(server.sin_addr.s_addr))) {
        printf("The given address '%s' is not multicast\n",
               inet_ntoa(server.sin_addr));
        exit(1);
    }

    /* create socket */
    soketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (soketfd < 0) {
        printf("Cannot create socket\n");
        exit(1);
    }

    /* bind any port number */
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = htonl(INADDR_ANY);
    client.sin_port = htons(0);

    if (bind(soketfd, (struct sockaddr *)&client, sizeof(client)) < 0) {
        perror("bind error");
        exit(1);
    }

    if (setsockopt(soketfd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0) {
        printf("Cannot set ttl = %d \n", ttl);
        exit(1);
    }

    printf("Sending data on multicast group '%s' \n", inet_ntoa(server.sin_addr));

    /* for (i = 2; i < argc; i++) {
        temp = sendto(soketfd, argv[i], strlen(argv[i]) + 1, 0, (struct sockaddr *)&server, sizeof(server));

        if (temp < 0) {
            printf("Cannot send data %d\n", i - 1);
            close(soketfd);
            exit(1);
        }
    } */
    strcpy(timbal, ctime(&masa));

    sendto(soketfd, timbal, 1024, 0, (struct sockaddr *)&server, sizeof(server));
    close(soketfd);
    return 0;
}