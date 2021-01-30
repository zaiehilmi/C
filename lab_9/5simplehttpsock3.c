//Latihan 9-5 - use any active IP address instead of loopback address

#include <errno.h>
#include <netdb.h>

#include "arpa/inet.h"

#define SAIZ 1024
#define BACKLOG 10

void report(struct sockaddr_in *server);

void setHttpHeader(char httpHeader[]) {
    FILE *htmldata = fopen("index.html", "r");

    char line[100];
    char responseData[8000];
    while (fgets(line, 100, htmldata) != 0)
        strcat(responseData, line);

    strcat(httpHeader, responseData);
}

int main(void) {
    char httpHeader[8000] = "HTTP/1.1 200 OK\r\n";
    int soketfd, ls, soketfd_cli;

    struct sockaddr_in server;

    soketfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8001);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(soketfd, (struct sockaddr *)&server, sizeof(server));
    ls = listen(soketfd, BACKLOG);
    if (ls < 0) {
        printf("Ralat: Server tidak mendengar\n");
        return 1;
    }

    report(&server);
    setHttpHeader(httpHeader);

    while (1) {
        soketfd_cli = accept(soketfd, NULL, NULL);
        send(soketfd_cli, httpHeader, sizeof(httpHeader), 0);

        close(soketfd_cli);
    }
    return 0;
}

void report(struct sockaddr_in *pelayan) {
    char timbalhos[INET6_ADDRSTRLEN];
    char timbalservis[NI_MAXSERV];
    socklen_t addrlen = sizeof(*pelayan);

    int err = getnameinfo(
        (struct sockaddr *)pelayan,
        addrlen,
        timbalhos,
        sizeof(timbalhos),
        timbalservis,
        sizeof(timbalservis),
        NI_NUMERICHOST);

    if (err != 0)
        printf("Tak berfungsi lahhh!!\n");

    printf("\n\n\tServer mendengar pada http://%s:%s\n", timbalhos, timbalservis);
}