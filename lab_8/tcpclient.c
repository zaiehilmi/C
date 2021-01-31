#include <string.h>

#include "arpa/inet.h"

#define PORT 5000
#define MAXLINE 1024

int main() {
    int soketfd, n, pjg;
    char timbal[MAXLINE];
    char *mesej = "Hello Server";

    struct sockaddr_in server;

    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soketfd < 0) {
        printf("Gagal mencipta soket\n");
        exit(0);
    }

    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("172.31.142.128");
    server.sin_port = htons(PORT);

    n = connect(soketfd, (struct sockaddr *)&server, sizeof(server));
    if (n < 0)
        printf("Ralat sambungan\n");

    bzero(timbal, sizeof(timbal));
    strcpy(timbal, "Hello Server");

    write(soketfd, timbal, sizeof(timbal));
    printf("Mesej daripada server: ");
    read(soketfd, timbal, sizeof(timbal));

    puts(timbal);
    close(soketfd);
}