#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>

#define MAX_THREADS 4
#define MAX_INPUT_SIZE 1024

typedef struct {
    int *array;
    int left;
    int right;
    sem_t *sem;
    pthread_mutex_t *mutex;
    int *active_threads;
} thread_data_t;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *array, int left, int right) {
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[right]);
    return i + 1;
}

void *parallel_quicksort(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int *array = data->array;
    int left = data->left;
    int right = data->right;
    sem_t *sem = data->sem;
    pthread_mutex_t *mutex = data->mutex;
    int *active_threads = data->active_threads;

    if (left < right) {
        int pi = partition(array, left, right);

        if (*active_threads < MAX_THREADS) {
            pthread_mutex_lock(mutex);
            (*active_threads)++;
            pthread_mutex_unlock(mutex);

            thread_data_t left_data = {array, left, pi - 1, sem, mutex, active_threads};
            thread_data_t right_data = {array, pi + 1, right, sem, mutex, active_threads};

            pthread_t left_thread, right_thread;
            pthread_create(&left_thread, NULL, parallel_quicksort, &left_data);
            pthread_create(&right_thread, NULL, parallel_quicksort, &right_data);

            pthread_join(left_thread, NULL);
            pthread_join(right_thread, NULL);

            pthread_mutex_lock(mutex);
            (*active_threads)--;
            pthread_mutex_unlock(mutex);
        } else {
            thread_data_t left_data = {array, left, pi - 1, sem, mutex, active_threads};
            thread_data_t right_data = {array, pi + 1, right, sem, mutex, active_threads};
            parallel_quicksort(&left_data);
            parallel_quicksort(&right_data);
        }
    }

    return NULL;
}

int main() {
    char input[MAX_INPUT_SIZE];
    int array[MAX_INPUT_SIZE];
    int array_size = 0;

    printf("Enter the array elements separated by spaces: ");
    fgets(input, MAX_INPUT_SIZE, stdin);

    char *token = strtok(input, " ");
    while (token != NULL) {
        while (isspace(*token)) token++;
        if (*token == '\0') break;

        array[array_size++] = atoi(token);
        token = strtok(NULL, " ");
    }

    sem_t sem;
    pthread_mutex_t mutex;
    int active_threads = 0;

    sem_init(&sem, 0, MAX_THREADS);
    pthread_mutex_init(&mutex, NULL);

    thread_data_t data = {array, 0, array_size - 1, &sem, &mutex, &active_threads};

    pthread_t main_thread;
    pthread_create(&main_thread, NULL, parallel_quicksort, &data);
    pthread_join(main_thread, NULL);

    sem_destroy(&sem);
    pthread_mutex_destroy(&mutex);

    printf("Sorted array: ");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
