//Latihan 9-3 - HTTP server display the output shown in Figure 9-7
#include "arpa/inet.h"

#define PORT 8080

int main(int argc, char const *argv[]) {
    int soketfd, soketfd_baru, temp;
    long nbaca;
    char timbal[30000] = {0};
    // char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 30\n\n Hello, network programming!";
    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<!DOCTYPE html> <html> <head> <title>Hello from network programming course</title>"
        "<style>body { background-color: #91 }"
        "h1 { font-size:3cm; text-align: center; color: yellow;"
        " text-shadow: 0 0 2mm green}</style></head>"
        "<body><h1>Hello Network Programmer </h1></body></html>\r\n";

    struct sockaddr_in server;
    int addrlen = sizeof(server);

    soketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (soketfd == 0) {
        perror("gagal mencipta soket\n");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    memset(server.sin_zero, '\0', sizeof(server.sin_zero));
    temp = bind(soketfd, (struct sockaddr *)&server, sizeof(server));
    if (temp < 0) {
        perror("Ralat untuk mengikat\n");
        exit(EXIT_FAILURE);
    }
    if (listen(soketfd, 10) < 0) {
        perror("Ralat untuk mendengar\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("\n+++++++++ Menunggu sambungan baharu +++++++++\n\n");
        soketfd_baru = accept(soketfd, (struct sockaddr *)&server, (socklen_t *)&addrlen);
        if (soketfd_baru < 0) {
            perror("Ralat penerimaan\n");
            exit(EXIT_FAILURE);
        }

        nbaca = read(soketfd_baru, timbal, 30000);
        printf("%s\n", timbal);

        write(soketfd_baru, response, strlen(response));
        printf("-------------- Mesej Hello dihantar --------------\n");
        close(soketfd_baru);
    }

    return 0;
}