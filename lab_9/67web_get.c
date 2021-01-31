//Latihan 9-6 - guna url selain ukm
//Latihan 9-7 - buat comment

#include <errno.h>
#include <netdb.h>
#include <time.h>

#include "arpa/inet.h"

#define TIMEOUT 5.0
#define ISVALIDSOCKET(s) ((s) >= 0)

void parse_url(char *url, char **hostname, char **port, char **path) {
    printf("URL: %s\n", url);

    char *p;
    p = strstr(url, "://");

    //senaraikan berapa jenis protokol yang ada
    char *protocol = 0;
    if (p) {
        protocol = url;
        *p = 0;
        p += 3;

    } else
        p = url;

    if (protocol) {
        if (strcmp(protocol, "http")) {
            fprintf(stderr, "Protokol tidak diketahui %s. hanya 'http' disokong\n", protocol);
            exit(1);
        }
    }

    *hostname = p;
    while (*p && *p != ':' && *p != '/' && *p != '#') ++p;

    //hos akan gunakan port 80
    *port = "80";
    if (*p == ':') {
        *p++ = 0;
        *port = p;
    }

    while (*p && *p != '/' && *p != '#') ++p;

    //senaraikan perjalanan
    *path = p;

    while (*p && *p != '#') ++p;

    if (*p == '#') *p = 0;

    //paparkan nama hos, port, dan perjalanan
    printf("hostname: %s\n", *hostname);
    printf("port: %s\n", *port);
    printf("path: %s\n", *path);
}

void send_request(int s, char *hostname, char *port, char *path) {
    //secara keseluruhan ialah untuk menghantar permintaan untuk menggunakan service ke server
    char buffer[2048];

    sprintf(buffer, "GET/%s HTTP/1.1\r\n", path);
    sprintf(buffer + strlen(buffer), "Host: %s: %s\r\n", hostname, port);
    sprintf(buffer + strlen(buffer), "Connection: close\r\n");
    sprintf(buffer + strlen(buffer), "User-Agent: honpwc web_get 1.0\r\n");
    sprintf(buffer + strlen(buffer), "\r\n");

    send(s, buffer, strlen(buffer), 0);
    printf("sent Headers:%s\n", buffer);
}

int connect_to_host(char *hostname, char *port) {
    //secara keseluruhan untuk membuat sambungan ke hos

    printf("Configuration remote address...\n");
    struct addrinfo hints, *peer_addr;

    memset(&hints, 0, sizeof(hints));

    hints.ai_socktype = SOCK_STREAM;
    //Translate name of a service location and/or a service name to set of socket addresses.
    if (getaddrinfo(hostname, port, &hints, &peer_addr)) {
        fprintf(stderr, "getaddrinfo failed. (%d)\n", errno);
        exit(1);
    }

    printf("Remote address is ");
    char address_buffer[100];
    char service_buffer[100];

    //Translate a socket address to a location and service name
    getnameinfo(peer_addr->ai_addr, peer_addr->ai_addrlen,
                address_buffer, sizeof(address_buffer),
                service_buffer, sizeof(service_buffer),
                NI_NUMERICHOST);
    printf("%s %s\n", address_buffer, service_buffer);
    printf("Creating socket...\n");
    int server;

    //bina soket
    server = socket(peer_addr->ai_family, peer_addr->ai_socktype, peer_addr->ai_protocol);
    if (!ISVALIDSOCKET(server)) {
        fprintf(stderr, "socket() failed. (%d)\n", errno);
        exit(1);
    }

    //sambungan ke server
    printf("Connecting...\n");
    if (connect(server, peer_addr->ai_addr, peer_addr->ai_addrlen)) {
        fprintf(stderr, "connect() failed. (%d)\n", errno);
        exit(1);
    }
    freeaddrinfo(peer_addr);
    printf("Connected\n\n");

    return server;
}

int main(int argc, char *argv[]) {
#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif
    //masukkan alamat ip pada argv[1]
    if (argc < 2) {
        fprintf(stderr, "usage: web_get url\n");
        return 1;
    }
    char *url = argv[1];

    char *hostname, *port, *path;
    parse_url(url, &hostname, &port, &path);

    //memulakan sambungan soket ke hos
    int server = connect_to_host(hostname, port);
    send_request(server, hostname, port, path);

    const clock_t start_time = clock();

#define RESPONSE_SIZE 32768
    char response[RESPONSE_SIZE + 1];
    char *p = response, *q;
    char *end = response + RESPONSE_SIZE;
    char *body = 0;

    enum { length,
           chunked,
           connection };
    int encoding = 0;
    int remaining = 0;

    while (1) {
        //selepas daripada timeout akan keluar error
        if ((clock() - start_time) / CLOCKS_PER_SEC > TIMEOUT) {
            fprintf(stderr, "timeout after %.2f seconds\n", TIMEOUT);
            return 1;
        }

        //jika buffer tak cukup ruang akan paparkan errror
        if (p == end) {
            fprintf(stderr, "out of buffer space\n");
            return 1;
        }

        //mengosongkan fd dan memasukkan server fd ke dalam pool reads
        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(server, &reads);

        struct timeval timeout;
        timeout.tv_sec = 0;        //saat
        timeout.tv_usec = 200000;  //mikrosaat

        if (select(server + 1, &reads, 0, 0, &timeout) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", errno);
            return 1;
        }

        //jika server sd telah dimasukkan dalam pool, maka statement ni jadi true dan boleh run block ni
        if (FD_ISSET(server, &reads)) {
            //proses penerimaan maklumat
            int bytes_received = recv(server, p, end - p, 0);
            if (bytes_received < 1) {
                if (encoding == connection && body) {
                    printf("%.*s", (int)(end - body), body);
                }

                printf("\nConnection closed by peer.\n");
                break;
            }

            /*printf("Received (%d bytes): '%.*s'",
                    bytes_received, bytes_received, p);*/

            p += bytes_received;
            *p = 0;

            if (!body && (body = strstr(response, "\r\n\r\n"))) {
                *body = 0;
                body += 4;

                printf("Received Headers:\n%s\n", response);

                q = strstr(response, "\nContent-Length: ");
                if (q) {
                    encoding = length;
                    q = strchr(q, ' ');
                    q += 1;
                    remaining = strtol(q, 0, 10);

                } else {
                    q = strstr(response, "\nTransfer-Encoding: chunked");
                    if (q) {
                        encoding = chunked;
                        remaining = 0;
                    } else {
                        encoding = connection;
                    }
                }
                printf("\nReceived Body:\n");
            }

            if (body) {
                if (encoding == length) {
                    if (p - body >= remaining) {
                        printf("%.*s", remaining, body);
                        break;
                    }
                } else if (encoding == chunked) {
                    do {
                        if (remaining == 0) {
                            if ((q = strstr(body, "\r\n"))) {
                                remaining = strtol(body, 0, 16);
                                if (!remaining) goto finish;
                                body = q + 2;
                            } else {
                                break;
                            }
                        }
                        if (remaining && p - body >= remaining) {
                            printf("%.*s", remaining, body);
                            body += remaining + 2;
                            remaining = 0;
                        }
                    } while (!remaining);
                }
            }  //if (body)
        }      //if FDSET
    }          //end while(1)
finish:

    printf("\nClosing socket...\n");
    close(server);

#if defined(_WIN32)
    WSACleanup();
#endif

    printf("Finished.\n");
    return 0;
}