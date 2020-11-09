//Latihan 3-4 belum siap

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <regex.h>

#define TRUE 1
#define FALSE 0

int benderapenggera = FALSE;
void tetapkanBendera(int isy);

void main(int argc, char **argv) {
    int masa, j;
    pid_t pid;
    static struct sigaction tindak;
	
    if(argc <= 2) {							//untuk tgk berapa statement diberi
        fprintf(stderr, "Format Penggunaan: ./%s <saat> <mesej>\n", __FILE__);
        exit(1);
    }

    masa = atoi(argv[1]);              //penukaran saat ke minit dan string ke int
    if(masa <= 0) {          		       //tengok masa yg dimasukkan betul atau tak
        fprintf(stderr, "Masalah pada input: masa\n");
        exit(2);
    }

    printf("sigalarm PID: %u\n", getpid());	//proses untuk hasilkan penggera
    printf("뭐야 갑자기. 잠깐만...\n");		  //menerima kejutn utk melakukan tugasan

    tindak.sa_handler = tetapkanBendera;
    sigaction(SIGALRM, &tindak, NULL);

    alarm(masa);

    pause();

    if(benderapenggera == TRUE) {
        for (j = 2; j < argc; j++){
            printf("\n%s", argv[j]);		//mencetak statement yg diterima
        }
        printf("\n");
        exit(0);
    }
}//utama tamat

void tetapkanBendera(int isy) {
    benderapenggera = TRUE;
}
