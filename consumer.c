#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

#define BUFFER_SIZE 2

// Define the shared data structure for the buffer
struct shared_data {
    int buffer[BUFFER_SIZE];
    int in;   // Index for inserting into the buffer
    int out;  // Index for removing from the buffer
};

sem_t *empty, *full, *mutex;
struct shared_data *shmem;

void* producer(void* arg) {
    int item = 1;
    while (1) {
        sem_wait(empty);
        sem_wait(mutex);

        // Produce an item and put it into the buffer
        shmem->buffer[shmem->in] = item;
        printf("Produced: %d\n", item);
        shmem->in = (shmem->in + 1) % BUFFER_SIZE;
        item++;

        sem_post(mutex);
        sem_post(full);
    }
}

int main() {
    // Create shared memory
    shmem = (struct shared_data*)mmap(NULL, sizeof(struct shared_data), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Initialize semaphores
    empty = sem_open("empty_sem", O_CREAT | O_EXCL, 0666, BUFFER_SIZE);
    full = sem_open("full_sem", O_CREAT | O_EXCL, 0666, 0);
    mutex = sem_open("mutex_sem", O_CREAT | O_EXCL, 0666, 1);

    shmem->in = 0;
    shmem->out = 0;

    pthread_t prod_thread;

    // Create a producer thread
    if (pthread_create(&prod_thread, NULL, producer, NULL)) {
        perror("Producer thread creation failed");
        return 1;
    }

    // Keep the program running
    while (1) {
        // You can add code to handle termination here.
    }

    // Cleanup and close resources (not shown here)
    return 0;
}
