#include "arpa/inet.h"

#define PORT 5000
#define MAXLINE 1024

int main(void) {
    int soketfd, n, pjg;
    char timbal[MAXLINE];
    char *mesej = "Hello Server";

    struct sockaddr_in server, client;

    //cipta soket fd
    soketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (soketfd < 0) {
        printf("Ralat mencipta soket\n");
        exit(0);
    }

    memset(&server, 0, sizeof(server));

    //mengisi maklumat server
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("172.28.246.24");

    //hantar hello ke server
    sendto(soketfd, (const char *)mesej, strlen(mesej), 0, (const struct sockaddr *)&server, sizeof(server));

    //menerima respon daripada server
    printf("Mesej daripada server: ");
    n = recvfrom(soketfd, (char *)timbal, MAXLINE, 0, (struct sockaddr *)&server, &pjg);
    puts(timbal);
    close(soketfd);
    return 0;
}