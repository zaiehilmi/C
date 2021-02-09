// Exercise 2-3

#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void* benang1(void* p);  //fungsi yang akan dijalankan oleh t1
void* benang2(void* p);  //fungsi yang akan dijalankan oleh t2

int kira = 0;
pthread_t sampel_benang;

int main(void) {
    //cipta 2 thread dan assign tugas yang akan dijalankan oleh thread tersebut dgn fungsi
    pthread_t t1, t2;
    pthread_create(&t1, NULL, benang1, NULL);
    pthread_create(&t2, NULL, benang2, NULL);

    //tunggu untuk fungsi selesai dijalankan oleh dua2 thread dan keluar program bersama
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // return 0;
}

void* benang1(void* p) {  //kira sampai 5 saat dan keluar

    while (1) {
        printf("Ini ialah benang 1 (Thread ID: %u)\n", pthread_self());
        sleep(1);
        kira++;

        if (kira == 5) {
            pthread_cancel(sampel_benang);
            pthread_exit(NULL);
        }
    }
}

void* benang2(void* p) {
    sampel_benang = pthread_self();

    while (1) {
        printf("Ini ialah benang 2 (Thread ID: %u)\n", sampel_benang);
        sleep(3);
    }
}