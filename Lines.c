#include "Lines.h"


Lines* dissectLines(char* buffer_ptr, uint32_t buffer_len) {
    Lines* l = malloc(sizeof(Lines));

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
    l->no_lines = no_lines;


    // allocate space for table of lines' pointers
    void* temp_lines_ptr = malloc(no_lines*sizeof(char*));
    if ( !temp_lines_ptr ) {
        fprintf(stderr, "Can't malloc in dissectLines\n");
        return NULL;
    }
    l->lines = (char**) temp_lines_ptr;


    // allocate memory to store the length of each line
    void* temp_lines_len = malloc(no_lines*sizeof(uint32_t));
    if ( !temp_lines_len ) {
        fprintf(stderr, "Can't malloc in dissectLines\n");
        return NULL;
    }
    l->lines_len = (uint32_t*) temp_lines_len;


    // determine each line's length
    uint32_t len = 0;
    uint32_t curr_line = 0;
    for ( uint32_t x = 0; x < buffer_len; x++ ) {
        if ( buffer_ptr[x] == '\n' ) {
            l->lines_len[curr_line] = len;
            curr_line++;
            len = 0;
        } else {
            len++;
        }
    }
    l->lines_len[curr_line] = len;


    // allocate a separate buffer for each line and then copy over
    // chars from buffer to the corresponding line
    uint32_t location = 0;
    for ( uint32_t x = 0; x < l->no_lines; x++ ) {
        void* new_line = malloc(l->lines_len[x]);
        if ( !new_line ) {
            fprintf(stderr, "Can't malloc line buffer in dissectLines\n");
            return NULL;
        }
        l->lines[x] = (char*) new_line;

        memcpy(l->lines[x], &buffer_ptr[location], l->lines_len[x]);
        location += l->lines_len[x]+1;
    }


    return l;
}


void freeLines(Lines* lines_ptr) {
    for ( uint32_t x = 0; x < lines_ptr->no_lines; x++ ) {
        free(lines_ptr->lines[x]);
    }
    free(lines_ptr->lines);

    free(lines_ptr->lines_len);

    free(lines_ptr);
}
