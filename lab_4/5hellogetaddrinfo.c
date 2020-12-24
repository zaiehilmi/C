//Latihan 4-5 - Modify hellogetaddrinfo.c to display the IP address of any domain name other than upm.edu.my
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char hostname[] = "twitter.com";  //the hostname we are looking up //
    //char hostname[] = "idawaty";         //the hostname we are looking up

    struct addrinfo *result;                     //to store results
    struct addrinfo hints;                       //to indicate information we want
    struct sockaddr_in *saddr;                   //to reference address
    int s;                                       //for error checking
    memset(&hints, 0, sizeof(struct addrinfo));  //zero out hints
    hints.ai_family = AF_INET;                   //we only want IPv4 addresses
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
