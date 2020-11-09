// Exercise 2-3

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void* benang1 (void* p);
void* benang2 (void* p);

int kira = 0;
pthread_t sampel_benang;

int main(void) {

    pthread_t t1, t2;
    pthread_create(&t1, NULL, benang1, NULL);
    pthread_create(&t2, NULL, benang2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    // return 0;
}

void* benang1 (void* p) {

    while(1) {
        printf("Ini ialah benang 1 (Thread ID: %u)\n", pthread_self());
        sleep(1);
        kira++;

        if (kira == 5) {
            pthread_cancel(sampel_benang);
            pthread_exit(NULL);
        }
        
    }
}

void* benang2 (void* p) {
    sampel_benang = pthread_self();

    while (1) {
        printf("Ini ialah benang 2 (Thread ID: %u)\n", sampel_benang);
        sleep(3);
    }
    
}