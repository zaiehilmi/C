#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SAIZTIMBAL 100

char *fifo = "penghantarfifo";  //fail fifo

int main(int argc, char **argv) {
    int fd, j, nwrite;
    char timbal[SAIZTIMBAL];

    if (argc < 2) {
        fprintf(stderr, "Format Penggunaan: ./%s <saat> <mesej>\n", __FILE__);
        exit(1);
    }

    fd = open(fifo, O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("Ralat pada open()\n");
        exit(2);
    }

    for (j = 0; j < argc; j++) {
        if (strlen(argv[j] > SAIZTIMBAL)) {
            printf("Mesej terlalu panjang\n");
            continue;
        }

        strcpy(timbal, argv[j]);

        nwrite = write(fd, timbal, SAIZTIMBAL - 1);
        if (nwrite == -1) {
            perror("Ralat pada write()");
        }
    }
    return 0;
}
