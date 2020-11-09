//Exercise 2-7

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 512
char namafail[] = "data.txt";
FILE *fail;

int main(int argc, char const *argv[]) {
    int nread;
    int buf[SIZE];
    char kandungan[1028];
    
    int fd = open(namafail, O_RDWR);

    if (fd == -1) {
        printf("Gagal membuka fail \"%s\"\n", namafail);
        exit(1);
    }
     
    // nread = read(fd, buf, SIZE);
    // write(1, buf, nread);
    fail = fopen(namafail, "r");
    fscanf(fail, "%[^\n]", kandungan);

    // printf("%s\n", kandungan);
    printf("Jumlah aksara dalam fail \"%s\" = %d\n", namafail, strlen(kandungan));
    
    close(fd);
    fclose(fail);
    printf("\nMenutup fail \"%s\"...\n", namafail);
    exit(0);
    return 0;
}
