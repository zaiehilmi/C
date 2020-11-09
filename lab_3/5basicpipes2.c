//Latihan 3-5

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>

#define SAIZTIMBAL 100

char *mesej1 = "hai #1";
char *mesej2 = "hai #2";

int main(int argc, char const *argv[])
{
    char timbal[SAIZTIMBAL];
    int paip[2], j;
    int pid;

    if (pipe(paip) == -1) {
        perror("Ralat pada pipe()");
        exit(1);
    }

    pid = fork();

    switch (pid) {
        case -1:
            perror("Ralat pada fork()");
            break;

        case 0:
            write(paip[1], mesej1, SAIZTIMBAL);
            write(paip[1], mesej2, SAIZTIMBAL);
            break;
            
        default:
            for (j = 0; j < 2; j++) {
                read(paip[0], timbal, SAIZTIMBAL);
                printf("%s\n", timbal);
            }
        wait(NULL);        
    }    
    return 0;
}
