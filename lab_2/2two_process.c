//Exercise 2-2

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t pid;
    pid = fork();

    switch (pid) {
        case (-1): {
            perror("Terdapat masalah pada fork()");
            break;
        }
        case (0): {
            printf("Kes 0: \n--Proses anak = %d,\n--proses ibubapa = %d\n", getpid(), getppid());
            break;
        }
        default: {
            printf("Lalai: \n--Proses anak = %d, \n--proses ibubapa = %d\n", pid, getpid());
            wait(NULL);
            break;
        }
    }
    return 0;
}
