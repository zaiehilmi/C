// Latihan 3-3

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
 
// void kendaliIsyarat(int isy);

int main() {
    static struct sigaction tindak;
    // tindak.sa_handler = kendaliIsyarat;

    printf("Sebelum sigaction(), minta tekan [CTRL]+C!\n");
    sleep(5);

    signal(SIGINT, SIG_IGN);
    // sigaction(SIGCONT, &tindak, NULL);
    printf("Selepas sigaction(), minta tekan [CTRL]+C!\n");
    sleep(7);
    exit(0);
}

// void kendaliIsyarat(int isy){
//     printf("Menerima isyarat mencelah %d\n", isy);
// }
