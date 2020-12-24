//Latihan 4-1 - Modify hello_aton.c to use inet_addr() function

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct in_addr alamat;

    alamat.s_addr = inet_addr("10.4.3.1");
    // inet_aton("10.4.3.1", &alamat);  //convert dari string ke network
    printf("Hello %s\n", inet_ntoa(alamat));
}