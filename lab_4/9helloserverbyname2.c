//Latihan 4-9

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void main() {
    struct servent *info;
    char namaport[512] = "https";
    info = getservbyname(namaport, "udp");
    if (!info) {
        printf("Pelayan %s tidak wujud\n", namaport);
        exit(100);
    }

    printf("Port pelayan FTP: %d\n", ntohs(info->s_port));
}