//Latihan 4-6 - display the IP address of any domain name other than upm.edu.my and idawaty
//ralat pada gethostbyname()

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct hostent *namahos;
    struct in_addr alamatip;

    if (argc != 2) {
        printf("Pengunaan: %s namahos\n", argv[0]);
        exit(1);
    }
    namahos = gethostbyname(argv[1]);

    if (!namahos) {
        printf("Ralat pada gethostbyname()\n");
        exit(100);
    }

    printf("Nama: %s\n", namahos->h_name);
    alamatip = *(struct in_addr *)namahos->h_addr_list;
    printf("Alamat IP: %s\n", inet_ntoa(alamatip));

    return 0;
}