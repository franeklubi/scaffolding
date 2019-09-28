#include "Head.h"


Head genHead() {
   Head h = {0, '\0', false};
   return h;
}


char moveRight(
    Head* current_head_ptr, char** buffer_ptr, uint32_t* buffer_len
) {
    current_head_ptr->pos++;

    // if reached the end of the buffer and not destructive
    if ( current_head_ptr->pos >= *buffer_len
        && !current_head_ptr->destructive
    ) {
        return EOF;

    // if reached the end of the buffer and is destructive
    } else if ( current_head_ptr->pos >= *buffer_len ) {
        // append space before end of buffer
        append(buffer_ptr, buffer_len, ' ', 1);
        return ' ';
    }


    char next = *buffer_ptr[current_head_ptr->pos];

    // if reached the end of the line and not destructive
    if ( next == '\n' && !current_head_ptr->destructive ) {
        return EOF;


    // if reached the end of the line and is indeed destructive
    } else if ( next == '\n' ) {
        // prepend a space before '\n'
        insert(
            buffer_ptr, buffer_len, ' ', current_head_ptr->pos, 1
        );
        return ' ';
    }

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
    int32_t index_after = (int32_t)current_head_ptr->pos;
    index_after -= n;


    printf("GO LEFT INFO:\n");
    printf("\tindex_after: %i\n", index_after);
    printf("\tnewline_index: %i\n", newline_index);
    printf("\tto_beginning: %i\n", to_beginning);
    printf("\tcurr headpos: %i\n", current_head_ptr->pos);
    printf("\tcurr destructive: %i\n", current_head_ptr->destructive);
    printf("\tBUFFER LEN FUCKER: %i\n\n", *buffer_len);


    // if the index after moving would be negative prepend the difference
    // and set current_head_ptr' pos to 0
    if ( index_after < newline_index && current_head_ptr->destructive ) {

        // if the newline_index is at the beginning of a buffer just prepend it
        // with the difference of index_after
        if ( newline_index == 0 ) {
            insert(
                buffer_ptr, buffer_len, ' ',
                newline_index, newline_index-index_after
            );

        // but if newline_index is somewhere else in the buffer,
        // we need to insert the difference of
        // newline_index and abs(index_after)
        } else {
            printf("insertin\n");
            insert(
                buffer_ptr, buffer_len, ' ',
                newline_index, newline_index-index_after
            );
        }
        printf("NEWLINE HERE %i\n\n", newline_index);
        current_head_ptr->pos = newline_index;
        return ' ';

    // if it's non destructive, well - we have a garotte on hand
    } else if ( index_after < 0 ) {
        fprintf(stderr, "Exit due to moveLeft overflow\n");

        return EOF;
    }

    // of course there's always a possibility that we just want to move left
    // without going out of line's boundaries
    current_head_ptr->pos = index_after;
    char next = *buffer_ptr[current_head_ptr->pos];


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
