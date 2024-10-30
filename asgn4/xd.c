#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16
int main(int argc, char **argv) {
    if (argc > 2) {

        exit(1);
    }

    const char *file = (argc == 2) ? argv[1] : NULL;
    int fd = (file != NULL) ? open(file, O_RDONLY) : STDIN_FILENO;

    if (fd == -1) {

        exit(1);
    }
    char buffer[BUFFER_SIZE];
    ssize_t read_in;
    int buffer_index = 0; // index of the next character to be processed

    unsigned int start = 0;

    while (1) {
        // Read from stdin/file until buffer is full or EOF is reached
        while (buffer_index < BUFFER_SIZE) {
            read_in = read(fd, buffer + buffer_index, (size_t) BUFFER_SIZE - (size_t) buffer_index);
            if (read_in == 0) {
                // EOF reached, break out of inner loop
                break;
            }
            buffer_index += read_in;
        }

        // Process the buffer
        if (buffer_index <= 0) {
            break;
        }
        printf("%08x: ", start);

        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (i < buffer_index) {
                printf("%02x", (unsigned char) buffer[i]);
            } else {
                printf("  ");
            }

            if ((i & 1) == 1) {
                printf(" ");
            }
        }

        printf(" ");

        for (int i = 0; i < buffer_index; i++) {
            char c = buffer[i];
            printf("%c", isprint(c) ? c : '.');
        }

        printf("\n");

        // Shift the remaining characters to the beginning of the buffer
        for (int i = 0; i < BUFFER_SIZE - buffer_index; i++) {
            buffer[i] = buffer[buffer_index + i];
        }

        buffer_index = BUFFER_SIZE - buffer_index;

        start += BUFFER_SIZE;

        // If EOF was reached, break out of outer loop
        if (read_in == 0) {
            break;
        }
    }

    close(fd);
    return 0;
}
