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
        #ifdef _DEBUG
            fprintf(stderr, "Can't malloc in loadFile\n");
        #endif
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


bool insert(
    char** buffer_ptr, uint32_t* buffer_len, char c, uint32_t index, uint32_t n
) {
    // well you certainly can't insert here
    if ( index >= *buffer_len ) {
        #ifdef _DEBUG
            fprintf(stderr, "Trying to insert outside of bounds\n");
        #endif
        return false;
    }

    // malloc another buffer with the size of buffer_len+n
    (*buffer_len)+=n;
    void* temp_new_buffer_ptr = malloc(*buffer_len);
    if ( !temp_new_buffer_ptr ) {
        #ifdef _DEBUG
            fprintf(stderr, "Can't malloc temp buffer in insert\n");
        #endif
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
        #ifdef _DEBUG
            fprintf(stderr, "Can't realloc in append\n");
        #endif
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


bool checkExtension(char* filename, char* ext) {
    uint16_t filename_len = 0;
    uint16_t ext_len = 0;

    while ( filename[filename_len] ) {
        filename_len++;
    }
    while ( ext[ext_len] ) {
        ext_len++;
    }

    // if the filename is shorter or the same length as the extension
    // it'd not be considered as a valid extension, even if it contained ext
    if ( ext_len >= filename_len ) {
        #ifdef _DEBUG
            fprintf(stderr, "Filename can't contain extension \"%s\"\n", ext);
        #endif
        return false;
    }

    // check if the last characters of filename are the same as in ext
    bool check = false;
    if ( strcmp(filename+(filename_len-ext_len), ext) == 0 ) {
        check = true;
    }


    return check;
}
