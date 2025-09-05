#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

/**
 * InputBuffer: it's a wrapper to store data
 */
typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

/**
 *  Introduces a prompt to the user
 *  before taking input from the user
 */
void prompt_print() {
    printf("sdb > ");
}

/**
 *
 * @param lineptr : a pointer to the variable we use to point to the buffer containing the read line.
 *                  if it set to NULL, it gets mallocated by getline() and should be freed by the user,
 *                  even if the command fails
 * @param n : a pointer to the variable we use to save the size of allocated buffer.
 * @param stream : the input stream to read from. We’ll be reading from standard input.
 * @return value: the number of bytes read, which may be less than the size of the buffer
 */
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

/**
 *
 * @param input_buffer : reads users input
 */
void read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read < 0) {
        printf("Error reading input");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

int main(int argc, char* argsv[]) {
    InputBuffer* input_buffer = new_input_buffer();

    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }

    return 0;
}