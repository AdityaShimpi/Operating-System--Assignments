#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 3
#define MAX_PRODUCED 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty; // Semaphore to track empty slots in the buffer
sem_t full; // Semaphore to track filled slots in the buffer
pthread_mutex_t mutex; // Mutex for accessing the buffer

void *producer(void *arg) {
    int producer_id = *((int *)arg);
    int produced = 0;
    while (produced < MAX_PRODUCED) {
        // Produce item
        sleep(1); // Simulate production time
        int item = rand() % 100;
        
        // Wait for empty slot
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        // Add item to buffer
        buffer[in] = item;
        printf("Producer %d produced item: %d\n", producer_id, item);
        in = (in + 1) % BUFFER_SIZE;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        
        produced++;
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int consumer_id = *((int *)arg);
    int consumed = 0;
    while (consumed < MAX_PRODUCED * NUM_PRODUCERS / NUM_CONSUMERS) {
        // Wait for full slot
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        // Remove item from buffer
        int item = buffer[out];
        printf("Consumer %d consumed item: %d\n", consumer_id, item);
        out = (out + 1) % BUFFER_SIZE;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        
        consumed++;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i + 1;
        pthread_create(&producer_threads[i], NULL, producer, (void *)&producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumer_threads[i], NULL, consumer, (void *)&consumer_ids[i]);
    }

    // Join producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    // Join consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
