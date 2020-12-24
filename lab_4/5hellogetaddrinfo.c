//Latihan 4-5 - Modify hellogetaddrinfo.c to display the IP address of any domain name other than upm.edu.my
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char hostname[] = "twitter.com";  //nama hos untuk dapatkan ip

    struct addrinfo *result;                     //simpan dalam ni
    struct addrinfo hints;                       //demand apa info yang kita nak
    struct sockaddr_in *saddr;                   //rujukan alamat
    int s;                                       //cek ralat
    memset(&hints, 0, sizeof(struct addrinfo));  //tukar kandungan hints nilai zero
    hints.ai_family = AF_INET;                   //kita nak ipv4 so gunakan AF_INET
    //Convert the hostname to an address
    if ((s = getaddrinfo(hostname, NULL, &hints, &result)) != 0) {
        fprintf(stderr, "getaddrtnfo: %s\n", gai_strerror(s));
        exit(1);
    }

    //convert generic socket address to inet socket address
    saddr = (struct sockaddr_in *)result->ai_addr;
    //print the address
    printf("Hello %s\n", inet_ntoa(saddr->sin_addr));
    //free the addrtnfo struct
    freeaddrinfo(result);
}
