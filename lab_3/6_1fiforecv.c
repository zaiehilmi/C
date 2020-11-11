#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define SAIZTIMBAL 100

char *fifo = "penghantaranfifo";

int main(int argc, char const *argv[])
{
    int fd; 
    char timbal[SAIZTIMBAL];
    
    int binafail = mkfifo(fifo, 0766);
    if (binafail == -1 && errno != EEXIST) {
        perror("Ralat pada mkfifo()\n");
        exit(1);
    }
    
    fd = open(fifo, O_RDWR);
    if (fd < 0) {
        perror("Ralat pada open()\n");
        exit(2);
    }

    for (;;) {
        if (read(fd, timbal, SAIZTIMBAL) < 0)
            perror("Ralat pada read()\n");

        printf("Diterima: %s\n", timbal);
    }
    return 0;
}
