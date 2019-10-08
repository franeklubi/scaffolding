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


bool insertLines(
    Lines* lines_ptr, uint32_t index, uint32_t line_n, uint32_t n
) {
    if ( index >= lines_ptr->no_lines ) {
        fprintf(stderr, "Out of bounds in insertLines\n");
        return false;
    }


    // expanding lines
    if ( !_expandLines(lines_ptr, line_n) ) {
        fprintf(stderr, "Can't realloc in insertLines\n");
        return false;
    }


    // shiftin boi
    for ( uint32_t x = 0; x < lines_ptr->no_lines-line_n-index; x++ ) {
        // shift lines' pointers
        lines_ptr->lines[lines_ptr->no_lines-1-x] =
            lines_ptr->lines[lines_ptr->no_lines-1-x-line_n];

        // shift line len's values
        lines_ptr->lines_len[lines_ptr->no_lines-1-x] =
            lines_ptr->lines_len[lines_ptr->no_lines-1-x-line_n];
    }


    if ( !_makeLines(lines_ptr, index, line_n, n) ) {
        fprintf(stderr, "Can't make lines in insertLines\n");
        return false;
    }


    return true;
}


bool appendLines(Lines* lines_ptr, uint32_t line_n, uint32_t n) {
    // expanding lines
    if ( !_expandLines(lines_ptr, line_n) ) {
        fprintf(stderr, "Can't realloc in appendLines\n");
        return false;
    }

    // filling lines in
    if ( !_makeLines(lines_ptr, lines_ptr->no_lines-line_n, line_n, n) ) {
        fprintf(stderr, "Can't make lines in appendLines\n");
        return false;
    }


    return true;
}


bool _expandLines(Lines* lines_ptr, uint32_t line_n) {
    // realloc lines buffer
    lines_ptr->no_lines+=line_n;
    void* temp_new_lines_ptr = realloc(
        lines_ptr->lines,
        lines_ptr->no_lines*sizeof(char*)
    );
    if ( !temp_new_lines_ptr ) {
        fprintf(stderr, "Can't realloc in _expandLines\n");
        lines_ptr->no_lines-=line_n;
        return false;
    }
    lines_ptr->lines = temp_new_lines_ptr;

    // realloc lines' length buffer
    void* temp_new_lines_len_ptr = realloc(
        lines_ptr->lines_len,
        lines_ptr->no_lines*sizeof(uint32_t)
    );
    if ( !temp_new_lines_len_ptr ) {
        fprintf(stderr, "Can't realloc in _expandLines\n");
        lines_ptr->no_lines-=line_n;
        return false;
    }
    lines_ptr->lines_len = temp_new_lines_len_ptr;

    return true;
}


bool _makeLines(Lines* lines_ptr, uint32_t index, uint32_t line_n, uint32_t n) {
    for ( uint32_t x = index; x < index+line_n; x++ ) {
        // setting line len to n
        lines_ptr->lines_len[x] = n;

        // allocating space for new lines
        void* new_line = malloc(n);
        if ( !new_line ) {
            fprintf(stderr, "Can't malloc line buffer in _makeLines\n");
            return false;
        }
        lines_ptr->lines[x] = (char*) new_line;

        memset(lines_ptr->lines[x], ' ', n);
    }

    return true;
}
