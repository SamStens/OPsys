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

void* consumer(void* arg) {
    while (1) {
        sem_wait(full);
        sem_wait(mutex);

        // Consume an item from the buffer
        int item = shmem->buffer[shmem->out];
        printf("Consumed: %d\n", item);
        shmem->out = (shmem->out + 1) % BUFFER_SIZE;

        sem_post(mutex);
        sem_post(empty);
    }
}

int main() {
    // Attach to the existing shared memory
    shmem = (struct shared_data*)mmap(NULL, sizeof(struct shared_data), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Open existing semaphores
    empty = sem_open("empty_sem", O_RDWR);
    full = sem_open("full_sem", O_RDWR);
    mutex = sem_open("mutex_sem", O_RDWR);

    pthread_t cons_thread;

    // Create a consumer thread
    if (pthread_create(&cons_thread, NULL, consumer, NULL)) {
        perror("Consumer thread creation failed");
        return 1;
    }

    // Keep the program running
    while (1) {
        // You can add code to handle termination here.
    }

    // Cleanup and close resources (not shown here)
    return 0;
}
