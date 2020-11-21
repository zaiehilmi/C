//latihan 3-6.1

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SAIZTIMBAL 100

void keluar(int isy);
char *fifo = "penghantaranfifo";  //nama fail fifo

int main(int argc, char *argv[]) {
    int fd;
    char timbal[SAIZTIMBAL];

    signal(SIGALRM, keluar);
    alarm(20);

    int binafail = mkfifo(fifo, 0766);  //bina fail fifo dgn kod akses 766
    if (binafail == -1 && errno != EEXIST) {
        perror("Ralat pada mkfifo()\n");
        exit(1);
    }

    binafail = mkfifo(fifo, 0744);
    if (binafail == -1 && errno != EEXIST) {
        perror("Ralat pada mkfifo()\n");
    }

    fd = open(fifo, O_RDWR);
    if (fd < 0) {  //buka fail fifo untuk memulakan read and write
        perror("Ralat pada open()\n");
        exit(2);
    }

    int baca;
    for (;;) {
        baca = read(fd, timbal, SAIZTIMBAL - 1);

        if (baca < 0)
            perror("Ralat pada read()\n");

        printf("Diterima: %s\n", timbal);
    }
    close(fd);
    return 0;
}

void keluar(int isyarat) {
    exit(3);
}
