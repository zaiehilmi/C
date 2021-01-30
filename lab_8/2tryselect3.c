//latihan 8-2 - it will wait for 2.05 seconds instead of 2.5 seconds

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define STDIN 0  //fd for std in

int main(void) {
    struct timeval tv;
    fd_set readfds;

    tv.tv_sec = 2;
    tv.tv_usec = 500000;

    printf("tidak membuat apa-apa atau tekan sebarang kekunci kemudian <enter>\n\n");

    FD_ZERO(&readfds);
    FD_SET(STDIN, &readfds);

    //Hanya readfds
    select(STDIN + 1, &readfds, NULL, NULL, &tv);

    if (FD_ISSET(STDIN, &readfds))
        printf("satu kekunci telah ditekan!\n");

    else
        printf("Masa tamat\n");

    return 0;
}