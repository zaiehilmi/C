//Latihan 3-5 letak close() kat

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>

#define SAIZTIMBAL 100

char *mesej1 = "hai #1";        //mesej yg mahu dihantar
char *mesej2 = "hai #2";

int main() {

    char timbal[SAIZTIMBAL];
    int paipfd[2], j;             //ada 2 ending point, read write
    int pid;

    if (pipe(paipfd) == -1) {     //membina dan membuka paip
        perror("Ralat pada pipe()");
        exit(1);
    }

    pid = fork();

    switch (pid) {
        case -1:
            perror("Ralat pada fork()");
            break;

        case 0:     //write 2 mesej ke parent via paipfd[1]
            write(paipfd[1], mesej1, SAIZTIMBAL);       
            write(paipfd[1], mesej2, SAIZTIMBAL);
            close(paipfd[1]);
            break;
            
        default:    //parent read guna paipfd[0]
            for (j = 0; j < 2; j++) {
                read(paipfd[0], timbal, SAIZTIMBAL);
                printf("%s\n", timbal);
            }
            close(paipfd[0]);
        wait(NULL);   //menunggu child utk selesai     
    }
    return 0;
}
