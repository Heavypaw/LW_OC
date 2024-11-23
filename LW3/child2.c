#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#include <utils.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    const char *filename = argv[1];
    printf("Child1: Trying to open file: %s\n", filename);

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    sem_t *semRead1 = sem_open("/sem_read1", 0);
    sem_t *semWrite = sem_open("/sem_write", 0);

    if (semRead1 == SEM_FAILED || semWrite == SEM_FAILED) {
        perror("semaphore's opening error");
        exit(-1);
    }

    int sharedFd = shm_open("/memory", O_RDWR, 0666);
    if (sharedFd == -1) {
        perror("shared memory connection error");
        exit(-1);
    }

    char *sharedMemory = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, sharedFd, 0);
    if (sharedMemory == MAP_FAILED) {
        perror("memory mapping error");
        exit(-1);
    }

    while (1) {
        printf("Child1: Waiting for semRead1\n");
        sem_wait(semRead1);
        printf("Child1: Received semRead1\n");
        if (!strcmp(sharedMemory, "q")) {
            printf("Child1: Received 'q', exiting\n");
            break;
        }

        printf("Child1: Reversing string: %s\n", sharedMemory);
        ReverseString(sharedMemory);
        printf("Child1: Writing reversed string to file: %s\n", sharedMemory);
        fprintf(file, "%s\n", sharedMemory);
        fflush(file);
        printf("Child1: Posting semWrite\n");
        sem_post(semWrite);
    }

    fclose(file);

    // Открываем файл для чтения и выводим его содержимое
    file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for reading");
        exit(1);
    }

    printf("Child1: Contents of file %s:\n", filename);
    char line[MEM_SIZE];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);

    sem_close(semRead1);
    sem_close(semWrite);

    munmap(sharedMemory, MEM_SIZE);
    close(sharedFd);

    return 0;
}