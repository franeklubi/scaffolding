#include "Head.h"


Head genHead() {
   Head h = {0, '\0', false};
   return h;
}


char moveRight(Head* current_head_ptr, char* buffer_ptr, uint32_t* buffer_len) {
    current_head_ptr->pos++;

    // if reached the end of the buffer and not destructive
    if ( current_head_ptr->pos >= *buffer_len
        && !current_head_ptr->destructive ) {

        return EOF;

    // if reached the end of the buffer and is destructive
    } else if ( current_head_ptr->pos >= *buffer_len ) {
        // append space before end of buffer
    }


    char next = buffer_ptr[current_head_ptr->pos];

    // if reached the end of the line and not destructive
    if ( next == '\n' && !current_head_ptr->destructive ) {
        return EOF;


    // if reached the end of the line and is indeed destructive
    } else if ( next == '\n' ) {
        // prepend a space before '\n'
    }

    return next;
};
