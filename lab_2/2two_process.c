//Exercise 2-2

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    pid_t pid;
    pid = fork();  //lahirkan anak daripada proses induk

    switch (pid) {
        case (-1): {  //jika terdapat error
            perror("Terdapat masalah pada fork()");
            break;
        }
        case (0): {  //berjaya fork dan lahir proses anak
            printf("Kes 0: \n--Proses anak = %d,\n--proses induk= %d\n", getpid(), getppid());
            break;
        }
        default: {  //pid untuk proses induk
            printf("Lalai: \n--Proses anak = %d, \n--proses induk = %d\n", pid, getpid());
            wait(NULL);  //tunggu child untuk mati dan NULL menunjukkan status tak perlu disimpan
            break;
        }
    }
    return 0;
}
