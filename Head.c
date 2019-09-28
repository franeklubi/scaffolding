#include "Head.h"


Head genHead() {
   Head h = {0, '\0', false};
   return h;
}


char moveRight(
    Head* current_head_ptr, char** buffer_ptr, uint32_t* buffer_len, uint32_t n
) {
    uint32_t to_end = lineEnd(current_head_ptr, buffer_ptr, buffer_len);

    // newline_index actually stores the index after the newline
    int32_t newline_index = (int32_t) current_head_ptr->pos+to_end;

    // the index after mod subtraction would look like this
    int32_t index_after = (int32_t) current_head_ptr->pos;
    index_after += n;


    // printf("GO RIGHT INFO:\n");
    // printf("\tindex_after: %i\n", index_after);
    // printf("\tnewline_index: %i\n", newline_index);
    // printf("\tto_end: %i\n", to_end);
    // printf("\tcurr headpos: %i\n", current_head_ptr->pos);
    // printf("\tcurr destructive: %i\n", current_head_ptr->destructive);
    // printf("\tbuffer len fucker: %i\n\n", *buffer_len);


    // if the index after moving would end up
    // outside the current line - insert/append the difference
    // and set current_head_ptr->pos to the end of the line
    if ( index_after > newline_index && current_head_ptr->destructive ) {

        // if the newline_index is at the end of the buffer
        // just append it with the difference of index_after
        if ( newline_index == *buffer_len-1 ) {
            append(
                buffer_ptr, buffer_len, ' ', index_after-newline_index
            );

        // but if newline_index is somewhere else in the buffer,
        // we need to use insert
        //
        // also we need to add 1 to newline_index since what newline_index
        // indicates really is the last index in the current line,
        // not the next real newline character like '\n'
        } else {
            insert(
                buffer_ptr, buffer_len, ' ',
                newline_index+1, index_after-newline_index
            );
        }
        current_head_ptr->pos = index_after;
        return ' ';

    // if it's non destructive we'll just put it gently to an eternal sleep
    } else if ( index_after > newline_index ) {
        fprintf(stderr, "Exit due to moveRight overflow\n");
        #define OOF EOF
        return OOF;
    }

    // of course there's always a possibility that we just want to move left
    // without going out of line's boundaries
    current_head_ptr->pos = index_after;
    char next = *buffer_ptr[current_head_ptr->pos];

    return next;
};


char moveLeft(
    Head* current_head_ptr, char** buffer_ptr, uint32_t* buffer_len, uint32_t n
) {

    uint32_t to_beginning = lineBeginning(
        current_head_ptr, buffer_ptr, buffer_len
    );

    // newline_index actually stores the index after the newline
    int32_t newline_index = (int32_t) current_head_ptr->pos-to_beginning;

    // the index after mod subtraction would look like this
    int32_t index_after = (int32_t) current_head_ptr->pos;
    index_after -= n;


    // printf("GO LEFT INFO:\n");
    // printf("\tindex_after: %i\n", index_after);
    // printf("\tnewline_index: %i\n", newline_index);
    // printf("\tto_beginning: %i\n", to_beginning);
    // printf("\tcurr headpos: %i\n", current_head_ptr->pos);
    // printf("\tcurr destructive: %i\n", current_head_ptr->destructive);
    // printf("\tbuffer len fucker: %i\n\n", *buffer_len);


    // if the index after moving would end up outside the current line
    // prepend the difference and set current_head_ptr->pos to newline_index
    if ( index_after < newline_index && current_head_ptr->destructive ) {
        insert(
            buffer_ptr, buffer_len, ' ',
            newline_index, newline_index-index_after
        );

        current_head_ptr->pos = newline_index;
        return ' ';

    // if it's non destructive, well - we have a garotte on hand
    } else if ( index_after < newline_index ) {
        fprintf(stderr, "Exit due to moveLeft overflow\n");
        return EOF;
    }

    // of course there's always a possibility that we just want to move left
    // without going out of line's boundaries
    current_head_ptr->pos = index_after;
    char next = (*buffer_ptr)[current_head_ptr->pos];


    return next;
}


uint32_t _lineEdgeCounter(
    Head* current_head_ptr, char** buffer_ptr, uint32_t* buffer_len,
    bool direction
) {
    int8_t d = -1;
    if ( direction ) {
        d = 1;
    }

    uint32_t index = current_head_ptr->pos;

    if (
        index >= *buffer_len
        || index < direction  // direction is still an int, right?
        || (*buffer_ptr)[index-d] == '\n'
    ) {
        return 0;
    }

    char next;
    do {
        index-=d;

        if ( direction ) {
            if ( index > 0 ) {
                next = (*buffer_ptr)[index-1];
            }
        } else {
            if ( index < *buffer_len-1 ) {
                next = (*buffer_ptr)[index-d];
            }
        }
    } while (
        next != '\n'
        && (
            direction?
                ( index > 0 )
                : ( index < *buffer_len-1 )
        )
    );

    return (current_head_ptr->pos - index) * d;
}
