//Latihan 5-7

#include <netdb.h>

#include "arpa/inet.h"

int main(int argc, char **argv) {
    int soketfd, ret;
    char *namahos, timbal[256];

    struct sockaddr_in alamat;
    struct hostent *infohos;
    struct servent *infopelayan;

    if (argc == 1)
        namahos = "localhost";

    else
        namahos = argv[1];

    infohos = gethostbyname(namahos);
    if (!infohos) {
        fprintf(stderr, "Tiada hos: %s\n", namahos);
        exit(1);
    }

    infopelayan = getservbyname("daytime", "tcp");
    if (!infopelayan) {
        fprintf(stderr, "Tiada pelayan waktu siang\n");
        exit(2);
    }

    printf("Port pelayan siang: %d\n", ntohs(infopelayan->s_port));

    //bina soket
    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    alamat.sin_family = AF_INET;
    alamat.sin_port = infopelayan->s_port;
    alamat.sin_addr = *(struct in_addr *)*(infohos->h_addr_list);

    ret = connect(soketfd, (struct sockaddr *)&alamat, sizeof(alamat));
    if (ret < 0) {
        perror("ralat sambungan\n");
        exit(3);
    }

    ret = read(soketfd, timbal, sizeof(timbal));
    timbal[ret] = '\0';
    printf("Keputusan: %s dan %d bytes telah dibaca\n", timbal, ret);

    close(soketfd);

    return 0;
}