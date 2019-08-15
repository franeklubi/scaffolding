#include "Head.h"


Head genHead() {
   Head h = {0, '\0', false};
   return h;
}


char moveRight(Head* current_head_ptr, char* buffer_ptr, uint32_t* buffer_len) {
    current_head_ptr->pos++;

    // if reached the end of the buffer and not destructive
    if ( current_head_ptr->pos >= *buffer_len
        && !current_head_ptr->destructive
    ) {
        return EOF;

    // if reached the end of the buffer and is destructive
    } else if ( current_head_ptr->pos >= *buffer_len ) {
        // append space before end of buffer
        buffer_ptr = append(buffer_ptr, buffer_len, ' ');
        return ' ';
    }


    char next = buffer_ptr[current_head_ptr->pos];

    // if reached the end of the line and not destructive
    if ( next == '\n' && !current_head_ptr->destructive ) {
        return EOF;


    // if reached the end of the line and is indeed destructive
    } else if ( next == '\n' ) {
        // prepend a space before '\n'
        buffer_ptr = insert(buffer_ptr, buffer_len, ' ', current_head_ptr->pos);
        return ' ';
    }

    return next;
};


char moveLeft(Head* current_head_ptr, char* buffer_ptr, uint32_t* buffer_len) {

    // since the pos is an unsigned value, we don't want to accidentaly
    // overflow it by decrementing it just yet, do we?
    if ( current_head_ptr->pos == 0
        && current_head_ptr->destructive
    ) {
        // prepend buffer at position 0 and keep the index intact if destructive
        buffer_ptr = prepend(buffer_ptr, buffer_len, ' ');
        return ' ';
    } else if ( current_head_ptr->pos == 0 ) {

        // i mean, we have to prevent overflow at all costs >:(, also it's
        // meant to trip at the either end of the line
        return EOF;
    }


    current_head_ptr->pos--;
    char next = buffer_ptr[current_head_ptr->pos];

    // if reached the end of the line and not destructive
    if ( next == '\n' && !current_head_ptr->destructive ) {
        return EOF;


    // if reached the end of the line and wants to fucking ram past thru
    } else if ( next == '\n' ) {
        // we say nah you stay on the same line and
        // insert a space after '\n'
        current_head_ptr->pos++;
        buffer_ptr = insert(buffer_ptr, buffer_len, ' ', current_head_ptr->pos);
    }

    return next;
}
