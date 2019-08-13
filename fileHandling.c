#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


uint32_t getSize(FILE* file) {
    fseek(file, 0L, SEEK_END);
    uint32_t size = ftell(file);
    rewind(file);

    return size;
}


char* loadFile(FILE* file, uint32_t file_size) {
    char* start_ptr = (char*) malloc(file_size);
    for ( uint32_t x = 0; x < file_size; x++ ) {
        char read_character = fgetc(file);
        if ( read_character == EOF && x != file_size-1 ) {
            fprintf(stderr, "Problem with reading file at %i", x);
        }
        start_ptr[x] = read_character;
    }

    return start_ptr;
}


char* insert(char* buffer_ptr, uint32_t* buffer_len, char c, uint32_t index) {

    // mitigate this issue by just not giving a fuck
    if ( index >= *buffer_len ) {
        fprintf(stderr, "Index bigger than buffer len");
        return buffer_ptr;
    }

    // make another buffer to store the values after index, also - the naming
    // is fine, it's a temporary pointer to a temp buffer
    void* temp_temp_buffer_ptr = malloc(*buffer_len-index);
    if ( !temp_temp_buffer_ptr ) {
        fprintf(stderr, "Can't malloc temp buffer\n");
        return buffer_ptr;
    }
    char* temp_buffer_ptr = (char*) temp_temp_buffer_ptr;

    // copy temp values
    for ( uint32_t x = 0; x < *buffer_len - index; x++ ) {
        temp_buffer_ptr[x] = buffer_ptr[x+index];
    }


    (*buffer_len)++;
    void* temp_new_buffer_ptr = realloc(buffer_ptr, *buffer_len);
    if ( !temp_new_buffer_ptr ) {
        fprintf(stderr, "Can't realloc\n");

        // don't forget to free the temp buffer silly ;)
        free(temp_buffer_ptr);

        return buffer_ptr;
    }

    // realloc worked baby
    char* new_buffer_ptr = (char*) temp_new_buffer_ptr;

    // replace the index
    new_buffer_ptr[index] = c;

    // unwind the temp_buffer_ptr
    for ( uint32_t x = 0; x < *buffer_len-index; x++ ) {
        new_buffer_ptr[x+index+1] = temp_buffer_ptr[x];
    }

    // free the temp_buffer_ptr
    free(temp_buffer_ptr);

    return new_buffer_ptr;
}
