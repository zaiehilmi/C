//Latihan 4-8 - Add useful comments in each of the codes

#include <ifaddrs.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main() {
    struct ifaddrs *alamat2;

    if (getifaddrs(&alamat2) == -1) {  //buat linked list dalam bentuk ifaddrs
        printf("Panggilan getifaddrs() gagal\n");
        return -1;
    }

    struct ifaddrs *alamat = alamat2;
    while (alamat) {
        if (alamat->ifa_addr == NULL) {  //jika takde value dalam variable ifa_addr, akan execute if else ni
            alamat = alamat->ifa_next;   //nilai ifa_next disimpan dalam alamat
            continue;
        }

        int klrga = alamat->ifa_addr->sa_family;  //nilai dalam sa_family diakses dan simpan dalam variable
        if (klrga == AF_INET || klrga == AF_INET6) {
            printf("%s\t", alamat->ifa_name);  //jenis sambungan dalam ifa_name akan dipaparkan
            printf("%s\t", klrga == AF_INET ? "IPv4" : "IPv6");

            char ap[100];
            const int saizklrga = klrga == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);

            getnameinfo(alamat->ifa_addr, saizklrga, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);  //mendapatkan info soket dan terjemah ke hos dan servisnya
            printf("\t%s\n", ap);
        }
        alamat = alamat->ifa_next;
    }
    freeifaddrs(alamat2);
    return 0;
}