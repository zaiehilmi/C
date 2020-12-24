//Latihan 4-9 - display the port number of any server other than FTP that uses TCP or UDP protocol in /etc/services

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void main() {
    struct servent *info;
    char namaport[512] = "https";
    info = getservbyname(namaport, "tcp");
    if (!info) {
        printf("Pelayan %s tidak wujud\n", namaport);
        exit(100);
    }

    printf("Port pelayan FTP: %d\n", ntohs(info->s_port));
}