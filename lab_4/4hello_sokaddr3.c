#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(void) {
    // TCP/IP socket address
    struct sockaddr_in sokettcp;

    // tukar alamat IP jadi inet address, simpan dalam sockaddr
    inet_aton("10.4.3.1", &(sokettcp.sin_addr));

    // print alamat IP
    printf("Hello %s\n", inet_ntoa(sokettcp.sin_addr));

    return 0;
}