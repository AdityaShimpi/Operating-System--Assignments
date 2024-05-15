#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER;

int resource = 0;
int readers_count = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    while (1) {
        pthread_mutex_lock(&read_lock);
        readers_count++;
        if (readers_count == 1) {
            pthread_mutex_lock(&write_lock);
        }
        pthread_mutex_unlock(&read_lock);

        // Reading shared resource
        printf("Reader %d is reading: %d\n", reader_id, resource);

        pthread_mutex_lock(&read_lock);
        readers_count--;
        if (readers_count == 0) {
            pthread_mutex_unlock(&write_lock);
        }
        pthread_mutex_unlock(&read_lock);

        sleep(1); // Simulating reading time
    }
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    while (1) {
        pthread_mutex_lock(&write_lock);

        // Writing to shared resource
        resource++;
        printf("Writer %d is writing: %d\n", writer_id, resource);

        pthread_mutex_unlock(&write_lock);

        sleep(1); // Simulating writing time
    }
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Creating reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]);
    }

    // Creating writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, (void *)&writer_ids[i]);
    }

    // Joining reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Joining writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
