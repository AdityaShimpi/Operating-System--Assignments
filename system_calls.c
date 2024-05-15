#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    // Process related system calls: fork, wait
    pid_t child_pid = fork();
    
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) { // Child process
        printf("Child process (PID: %d) is running.\n", getpid());
        printf("Child process is exiting.\n");
        exit(EXIT_SUCCESS);
    } else { // Parent process
        printf("Parent process (PID: %d) is waiting for child process (PID: %d) to finish.\n", getpid(), child_pid);
        wait(NULL);
        printf("Child process has finished. Parent process is continuing.\n");
    }

    // File related system calls: open, read, write, close
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); // Open or create file test.txt
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    const char *buffer = "Hello, this is a test file!\n";
    ssize_t bytes_written = write(fd, buffer, strlen(buffer)); // Write to the file
    if (bytes_written == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd); // Close the file

    fd = open("test.txt", O_RDONLY); // Open the file for reading
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char read_buffer[100];
    ssize_t bytes_read = read(fd, read_buffer, sizeof(read_buffer)); // Read from the file
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    read_buffer[bytes_read] = '\0'; // Null-terminate the read string
    printf("Read from file: %s", read_buffer);

    close(fd); // Close the file

    // Protection related system call: chmod
    if (chmod("test.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) { // Change permissions of test.txt
        perror("chmod");
        exit(EXIT_FAILURE);
    }

    printf("File permissions have been changed.\n");

    return 0;
}
