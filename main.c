#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    uint64_t x;
    uint64_t y;
    char op;
    uint64_t mod;
} Head;


Head genHead() {
    Head h = {0, 0, '\0', 0};
    return h;
}


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

bool interpret(
    char* buffer_ptr, uint32_t buffer_len, Head r_head, Head w_head
) {





    return true;
}


int main() {
    Head r_head = genHead();
    Head w_head = genHead();

    FILE* file = fopen("hw.scaf", "r");
        int32_t file_size = getSize(file);
        char* start_ptr = loadFile(file, file_size);
    fclose(file);

    bool success = interpret(start_ptr, file_size, r_head, w_head);

    if ( !success ) {
        printf("Some error occured, fuck off");
    }

    free(start_ptr);
}
