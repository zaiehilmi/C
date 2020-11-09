// Exercise 2-6

#include <stdio.h>
#include <unistd.h>

#define SIZE 512                                 //saiz buffer

int main(int argc, char const *argv[])
{
    int nread;
    char buf[SIZE];
    char mesej[] = "Masukkan input melalui papan kekunci anda:\n";
    char mesej2[] = "Ini ialah salinan input anda: \n";

    write(1, mesej, 44);
    for (int i = 0; (nread = read(0, buf, SIZE)) > 0; i++) {
        write(1, mesej2, 32);
        write(1, buf, nread); 
    }
    
    // while((nread = read(0, buf, SIZE)) > 0 ) {   //baca dari fd = 0 (keyboard)
    //     write(1, buf, nread);                    //papar pada fd = 1 (skrin)
    // }
    return 0;
}
