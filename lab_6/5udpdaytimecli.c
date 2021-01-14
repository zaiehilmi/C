//Latihan 6-5 - Enable the UDP daytime server port

#include <netdb.h>

#include "arpa/inet.h"

int main(int argc, char *argv[]) {
    int soketfd, pjg, ret;
    struct sockaddr_in alamat;

    char *namahos, timbal[256];
    struct hostent *infohos;
    struct servent *infocli;

    if (argc == 1)
        namahos = "localhost";
    else
        namahos = argv[1];

    infohos = gethostbyname(namahos);

    if (!infohos) {
        fprintf(stderr, "Tiada hos: %s\n ", namahos);
        exit(1);
    }

    infocli = getservbyname("daytime", "udp");

    if (!infocli) {
        fprintf(stderr, "Tiada Pelayan daytime \n");
        exit(1);
    }
    printf("Port Pelayan Daytime: %d\n", ntohs(infocli->s_port));

    //creating udp socket
    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    alamat.sin_family = AF_INET;
    alamat.sin_port = infocli->s_port;
    alamat.sin_addr = *(struct in_addr *)*(infohos->h_addr_list);

    pjg = sizeof(alamat);
    ret = connect(soketfd, (struct sockaddr *)&alamat, pjg);

    if (ret == -1) {
        perror("Ralat sambungan. \n");
        exit(1);
    }

    ret = read(soketfd, timbal, sizeof(timbal));
    timbal[ret] = '\0';
    printf("Keputusan: %s dan %d bytes dibaca \n", timbal, ret);

    close(soketfd);

    return 0;
}