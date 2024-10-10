#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe1[2]; 
    int pipe2[2]; 
    pid_t pid1, pid2;
    char filename1[BUFFER_SIZE], filename2[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    srand(time(NULL));

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { 
        close(pipe1[1]); 
        close(pipe2[0]); 

        dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);
        execl("./child", "child", NULL);

        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            close(pipe1[0]); 
            close(pipe2[1]);

            dup2(pipe2[0], STDIN_FILENO);
            close(pipe2[0]);

            execl("./child", "child", NULL);

            perror("execl");
            exit(EXIT_FAILURE);
        } else { 
            close(pipe1[0]);
            close(pipe2[0]);

            printf("Введите имя файла для child1: ");
            fgets(filename1, BUFFER_SIZE, stdin);
            filename1[strcspn(filename1, "\n")] = '\0'; 

            printf("Введите имя файла для child2: ");
            fgets(filename2, BUFFER_SIZE, stdin);
            filename2[strcspn(filename2, "\n")] = '\0'; 

            write(pipe1[1], filename1, strlen(filename1) + 1);
            write(pipe2[1], filename2, strlen(filename2) + 1);

            while (1) {
                printf("Введите строку: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; 

                if (strcmp(buffer, "exit") == 0) {
                    write(pipe1[1], buffer, strlen(buffer) + 1);
                    write(pipe2[1], buffer, strlen(buffer) + 1);
                    break;
                }

                if (rand() % 100 < 80) {
                    write(pipe1[1], buffer, strlen(buffer) + 1);
                } else {
                    write(pipe2[1], buffer, strlen(buffer) + 1);
                }
            }

            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
