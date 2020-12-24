//Latihan 4-7 - use inet_ntoa() function instead of inet_ntop() & Add useful comments in each of the codes

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    struct addrinfo petunjuk, *res, *ptr;
    int status;
    char rentetanip[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr, "Penggunaan: %s nama_hos\n", __FILE__);
        exit(10);
    }
    //gantikan nilai pada petunjuk dgn 0 dan seterusnya declare saiz untuk family dan socktype
    memset(&petunjuk, 0, sizeof(petunjuk));
    petunjuk.ai_family = AF_UNSPEC;
    petunjuk.ai_socktype = SOCK_STREAM;

    //proses untuk mendapatkan info berkaitan dgn website dipilih
    //dan paparkan error kalau tak dpt info
    status = getaddrinfo(argv[1], NULL, &petunjuk, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(20);
    }

    printf("Alamat IP untuk %s: \n\n", argv[1]);

    for (ptr = res; ptr != NULL; ptr = ptr->ai_next) {
        struct in_addr alamat;
        void *versiip;

        //dapatkan pointer ke alamatnya
        //IPv4
        if (ptr->ai_family == AF_INET) {
            //point ptr ke ai_addr untuk dapatkan alamat ip kemudian point ke sin_addr untuk akses alamat
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)ptr->ai_addr;

            alamat = ipv4->sin_addr;
            versiip = "IPv4";
        }
        //IPv6
        /* else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)ptr->ai_addr;

            alamat = &(ipv6->sin6_addr);
            versiip = "IPv6";
        } */

        //tukar IP ke rentetan untuk paparkan
        // inet_ntop(ptr->ai_family, alamat, rentetanip, sizeof(rentetanip));

        printf("%s: %s\n", versiip, inet_ntoa(alamat));
    }
    freeaddrinfo(res);
    return 0;
}
