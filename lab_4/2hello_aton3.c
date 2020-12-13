#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct in_addr alamat;

    inet_aton("10.4.3.1", &alamat);  //convert dari string ke network
    printf("Hello %s\n", inet_ntoa(alamat));
}