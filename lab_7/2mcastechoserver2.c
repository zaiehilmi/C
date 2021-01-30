//Latihan 7-2 - the received local time is displayed by the server
#include "arpa/inet.h"

#define MCAST_ECHOSERVER_PORT 49000
#define MSJ_MAX 100

int main(int argc, char *argv[]) {
    int soketfd, nbaca, clilen, temp;
    char msj[MSJ_MAX];

    struct ip_mreq mgroup;
    struct sockaddr_in server, client;
    struct in_addr mcast;

    if (argc != 2) {
        printf("CARA GUNA: %s <alamat mcast>\n", argv[0]);
        exit(1);
    }

    //memulakan alamat multicast group
    mcast.s_addr = inet_addr(argv[1]);

    //menyemak alamat yg diberi ialah multicast
    if (!IN_MULTICAST(ntohl(mcast.s_addr))) {
        printf("Alamat diberi %s ialah bukan multicast\n", inet_ntoa(mcast));
        exit(2);
    }

    //mencipta soket
    soketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (soketfd < 0) {
        printf("Tidak boleh mencipta soket\n");
        exit(3);
    }

    //mengikat port
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(MCAST_ECHOSERVER_PORT);

    temp = bind(soketfd, (struct sockaddr *)&server, sizeof(server));
    if (temp < 0) {
        printf("Tidak boleh mengikat port %d\n", MCAST_ECHOSERVER_PORT);
        exit(1);
    }

    //sertai multicast group
    mgroup.imr_multiaddr.s_addr = mcast.s_addr;
    mgroup.imr_interface.s_addr = htonl(INADDR_ANY);

    temp = setsockopt(soketfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mgroup, sizeof(mgroup));
    if (temp < 0) {
        printf("Tidak boleh menyertai multicast group '%s'\n", inet_ntoa(mcast));
        exit(3);
    } else {
        printf("Mendengar mgroup %s: %d\n", inet_ntoa(mcast), MCAST_ECHOSERVER_PORT);

        while (1) {
            clilen = sizeof(client);
            nbaca = recvfrom(soketfd, msj, MSJ_MAX, 0, (struct sockaddr *)&client, &clilen);
            if (nbaca < 0) {
                printf("Tidak boleh menerima data\n");
                continue;
            }

            printf("%s: daripada %s:%d pada %s: %s\n", argv[0], inet_ntoa(client.sin_addr), ntohs(client.sin_port), argv[1], msj);
        }
    }
    close(soketfd);
    return 0;
}