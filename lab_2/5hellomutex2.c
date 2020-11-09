// Exercise 2-5

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *CetakNombor(void *p);                          //isytihar fungsi

//global variables
pthread_mutex_t kunci;
int j;

int main(void) {

    pthread_t benang[4];
    j = 0;

    if (pthread_mutex_init(&kunci, NULL) != 0) {      //memulakan mutex
        printf("Gagal memulakan Mutex!\n");
        exit(1);
    }

    int sbntr[4];
    for (int i = 0; i < 4; i++) {
        sbntr[i] = i;
        pthread_create(&benang[i], NULL, CetakNombor, (void*) NULL);    //buat benang
        pthread_join(benang[i], NULL);                                  //seragamkan benang
    }
    return 0;
}

void *CetakNombor(void *p) {

    pthread_mutex_lock(&kunci);                      //mengunci hatimu
    int i = 0;
    j++;

    while (i < 5) {
        printf("%d\t", j);
        sleep(1);

        i++;
    }
    
    printf("...Selesai\n");
    pthread_mutex_unlock(&kunci);                    //terlerai kunci itu

}