#include "Head.h"


Head genHead() {
   Head h = {0, 0, '\0', false};
   return h;
}


char moveRight(
    Lines* buffer_ptr, Head* curr_head_ptr, uint32_t n
) {
    if ( !isLegalPosition(buffer_ptr, curr_head_ptr) ) {
        fprintf(stderr, "Illegal position in moveRight\n");
        return EOF;
    }

    uint32_t to_end = lineEnd(buffer_ptr, curr_head_ptr);

    // newline_index actually stores the index before the newline
    int32_t newline_index = (int32_t) curr_head_ptr->pos_x+to_end;

    // the index after mod addition would look like this
    uint32_t index_after = curr_head_ptr->pos_x;
    index_after += n;

    // if the index after moving would end up
    // outside the current line - append the difference
    // and set curr_head_ptr->pos_x to the end of the line
    if ( index_after > newline_index && curr_head_ptr->destructive ) {

        append(
            &buffer_ptr->lines[curr_head_ptr->pos_y],
            &buffer_ptr->lines_len[curr_head_ptr->pos_y],
            ' ', index_after-newline_index
        );

        curr_head_ptr->pos_x = index_after;
        return ' ';

    // if it's non destructive we'll just put it gently to an eternal sleep
    } else if ( index_after > newline_index ) {
        fprintf(stderr, "Exit due to moveRight overflow\n");
        #define OOF EOF
        return OOF;
    }

    // of course there's always a possibility that we just want to move right
    // without going out of line's boundaries
    curr_head_ptr->pos_x = index_after;
    char next = buffer_ptr->lines[curr_head_ptr->pos_y][curr_head_ptr->pos_x];

    return next;
};


char moveLeft(
    Lines* buffer_ptr, Head* curr_head_ptr, uint32_t n
) {
    if ( !isLegalPosition(buffer_ptr, curr_head_ptr) ) {
        fprintf(stderr, "Illegal position in moveRight\n");
        return EOF;
    }

    uint32_t to_beginning = lineBeginning(buffer_ptr, curr_head_ptr);

    // newline_index actually stores the index after the newline
    int32_t newline_index = (int32_t) curr_head_ptr->pos_x-to_beginning;

    // the index after mod subtraction would look like this
    int32_t index_after = (int32_t) curr_head_ptr->pos_x;
    index_after -= n;


    // if the index after moving would end up outside the current line
    // prepend the difference and set curr_head_ptr->pos_x to newline_index
    if ( index_after < newline_index && curr_head_ptr->destructive ) {
        insert(
            &buffer_ptr->lines[curr_head_ptr->pos_y],
            &buffer_ptr->lines_len[curr_head_ptr->pos_y],
            ' ', newline_index, newline_index-index_after
        );

        curr_head_ptr->pos_x = newline_index;
        return ' ';

    // if it's non destructive, well - we have a garotte on hand
    } else if ( index_after < newline_index ) {
        fprintf(stderr, "Exit due to moveLeft overflow\n");
        return EOF;
    }

    // of course there's always a possibility that we just want to move left
    // without going out of line's boundaries
    curr_head_ptr->pos_x = index_after;
    char next = buffer_ptr->lines[curr_head_ptr->pos_y][curr_head_ptr->pos_x];


    return next;
}


char moveDown(Lines* buffer_ptr, Head* curr_head_ptr, uint32_t n) {
    if ( !isLegalPosition(buffer_ptr, curr_head_ptr) ) {
        fprintf(stderr, "Illegal position in moveDown\n");
        return EOF;
    }

    uint32_t last_line_index = buffer_ptr->no_lines-1;

    // the pos_y after mod addition would look like this
    uint32_t pos_y_after = curr_head_ptr->pos_y + n;


    // check if lines head is gonna move through are not shorter than the
    // current x position; it's gonna be pretty bad otherwise
    int32_t check_until = pos_y_after;
    if ( check_until >= buffer_ptr->no_lines ) {
        check_until = buffer_ptr->no_lines-1;
    }
    for ( uint32_t y = curr_head_ptr->pos_y; y < last_line_index; y++ ) {
        if ( buffer_ptr->lines_len[y] < curr_head_ptr->pos_x ) {
            if ( curr_head_ptr->destructive ) {
                append(
                    &buffer_ptr->lines[y], &buffer_ptr->lines_len[y],
                    ' ', curr_head_ptr->pos_x - buffer_ptr->lines_len[y] + 1
                );
            } else {
                // imma end this program's whole career
                fprintf(stderr, "Exit due to moveDown overflow\n");
                return EOF;
            }
        }
    }

    // if the index after moving would end up
    // outside the entire buffer - append the difference in lines
    // and set curr_head_ptr->pos_y to the last line
    if ( pos_y_after > last_line_index && curr_head_ptr->destructive ) {

        appendLines(
            buffer_ptr, pos_y_after-last_line_index, curr_head_ptr->pos_x+1
        );

        curr_head_ptr->pos_y = pos_y_after;
        return ' ';

    // if it's non destructive - just tell me, i have a shotgun somewhere here
    } else if ( pos_y_after > last_line_index ) {
        fprintf(stderr, "Exit due to moveDown overflow\n");
        return EOF;
    }

    // if the position is going to be legal - just move down dude
    curr_head_ptr->pos_y = pos_y_after;
    char next = buffer_ptr->lines[curr_head_ptr->pos_y][curr_head_ptr->pos_x];

    return next;
}


char moveUp(Lines* buffer_ptr, Head* curr_head_ptr, uint32_t n) {
    if ( !isLegalPosition(buffer_ptr, curr_head_ptr) ) {
        fprintf(stderr, "Illegal position in moveUp\n");
        return EOF;
    }

    int32_t first_line_index = 0;

    // the pos_y after subtraction addition would look like this
    int32_t pos_y_after = (int32_t) curr_head_ptr->pos_y;
    pos_y_after -= n;


    // check if lines head is gonna move through are not shorter than the
    // current x position; yo not DRY at all. ill fix it ok?
    int32_t check_until = pos_y_after;
    if ( check_until < 0 ) {
        check_until = 0;
    }
    for ( int32_t y = curr_head_ptr->pos_y; y >= check_until; y-- ) {
        if ( buffer_ptr->lines_len[y] < curr_head_ptr->pos_x ) {
            if ( curr_head_ptr->destructive ) {
                append(
                    &buffer_ptr->lines[y], &buffer_ptr->lines_len[y],
                    ' ', curr_head_ptr->pos_x - buffer_ptr->lines_len[y] + 1
                );
            } else {
                // fuck my shit up
                fprintf(stderr, "Exit due to moveUp overflow\n");
                return EOF;
            }
        }
    }

    // if the index after moving would end up
    // outside the entire buffer - insert the difference in lines
    // and set curr_head_ptr->pos_y to the first line
    if ( pos_y_after < first_line_index && curr_head_ptr->destructive ) {
        insertLines(
            buffer_ptr, first_line_index, pos_y_after*-1, curr_head_ptr->pos_x+1
        );

        curr_head_ptr->pos_y = 0;
        return ' ';

        // if it's non destructive - just tell me, i have a shotgun somewhere here
    } else if ( pos_y_after < first_line_index ) {
        fprintf(stderr, "Exit due to moveUp overflow\n");
        return EOF;
    }

    // if the position is going to be legal - just move down dude
    curr_head_ptr->pos_y = pos_y_after;
    printf("YO Y(%i) X(%i)\n", curr_head_ptr->pos_y, curr_head_ptr->pos_x);
    char next = buffer_ptr->lines[curr_head_ptr->pos_y][curr_head_ptr->pos_x];

    return next;
}


int32_t _lineEdgeCounter(Lines* buffer_ptr, Head* head_ptr, bool direction) {
    // testing if the head is out of bounds
    if ( !isLegalPosition(buffer_ptr, head_ptr) ) {
        fprintf(stderr, "Out of bounds in _lineEdgeCounter\n");
        return -1;
    }

    if ( direction ) {
        return head_ptr->pos_x;
    }

    return buffer_ptr->lines_len[head_ptr->pos_y] - head_ptr->pos_x - 1;
}


bool isLegalPosition(Lines* buffer_ptr, Head* head_ptr) {
    return (
        head_ptr->pos_y < buffer_ptr->no_lines
        && head_ptr->pos_x < buffer_ptr->lines_len[head_ptr->pos_y]
    );
}
