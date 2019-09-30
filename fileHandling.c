#include "fileHandling.h"


uint32_t getSize(FILE* file) {
    fseek(file, 0L, SEEK_END);
    uint32_t size = ftell(file);
    rewind(file);

    return size;
}


char* loadFile(FILE* file, uint32_t file_size) {
    void* temp_start_ptr = malloc(file_size);
    if ( !temp_start_ptr ) {
        fprintf(stderr, "Can't malloc in loadFile\n");
        return temp_start_ptr;
    }
    char* start_ptr = (char*) temp_start_ptr;

    for ( uint32_t x = 0; x < file_size; x++ ) {
        char read_character = fgetc(file);
        if ( read_character == EOF && x != file_size-1 ) {
            fprintf(stderr, "Problem with reading file at %i\n", x);
        }
        start_ptr[x] = read_character;
    }

    return start_ptr;
}


Lines* dissectLines(char* buffer_ptr, uint32_t buffer_len) {
    Lines l;

    if ( buffer_len == 0 ) {
        fprintf(stderr, "Buffer length 0 in dissectLines\n");
        return NULL;
    }

    // determine number of lines ( the first one is implicit )
    uint32_t no_lines = 1;
    for ( uint32_t x = 0; x < buffer_len; x++ ) {
        if ( buffer_ptr[x] == '\n' ) {
            no_lines++;
        }
    }
    l.no_lines = no_lines;


    // allocate memory to store the length of each line
    void* temp_lines_len = malloc(no_lines*sizeof(uint32_t));
    if ( !temp_lines_len ) {
        fprintf(stderr, "Can't malloc in dissectLines\n");
        return NULL;
    }
    l.lines_len = (uint32_t*) temp_lines_len;


    Lines* l_ptr = &l;
    return l_ptr;
}


bool insert(
    char** buffer_ptr, uint32_t* buffer_len, char c, uint32_t index, uint32_t n
) {

    // mitigate this issue by just not giving a fuck
    if ( index >= *buffer_len ) {
        fprintf(stderr, "Index bigger than buffer len in insert\n");
        return false;
    }

    // malloc another buffer with the size of buffer_len+n
    (*buffer_len)+=n;
    void* temp_new_buffer_ptr = malloc(*buffer_len);
    if ( !temp_new_buffer_ptr ) {
        fprintf(stderr, "Can't malloc temp buffer in insert\n");
        (*buffer_len)-=n;
        return false;
    }
    char* new_buffer_ptr = (char*) temp_new_buffer_ptr;


    // insert n of chars c starting from index in new buffer
    for ( uint32_t x = 0; x < n; x++ ) {
        new_buffer_ptr[index+x] = c;
    }


    // copy the left part of the memory (if there is any to copy ofc)
    if ( index > 0 ) {
        memcpy(new_buffer_ptr, *buffer_ptr, index);
    }

    // copy the right part of the memory
    memcpy(&new_buffer_ptr[index+n], &(*buffer_ptr)[index], (*buffer_len)-n-index);


    free(*buffer_ptr);

    *buffer_ptr = new_buffer_ptr;

    return true;
}


bool append(char** buffer_ptr, uint32_t* buffer_len, char c, uint32_t n) {
    (*buffer_len)+=n;
    void* temp_new_buffer_ptr = realloc(*buffer_ptr, *buffer_len);
    if ( !temp_new_buffer_ptr ) {
        fprintf(stderr, "Can't realloc in append\n");
        (*buffer_len)-=n;
        return false;
    }
    char* new_buffer_ptr = (char*) temp_new_buffer_ptr;

    *buffer_ptr = new_buffer_ptr;

    for ( uint32_t x = 0; x < n; x++ ) {
        (*buffer_ptr)[*buffer_len-n+x] = c;
    }


    return true;
}
