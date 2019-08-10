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
