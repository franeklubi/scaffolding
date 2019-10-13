#ifndef HEAD_H
#define HEAD_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "fileHandling.h"
#include "Lines.h"


typedef struct {
    uint32_t pos_x;
    uint32_t pos_y;
    uint8_t mod;
    bool destructive;
} Head;


// returns filled Head struct
Head genHead();

// moveRight increments head's pos and returns mod it's standing on or EOF
// if reached newline or the end of the buffer,
// however - if destructive, it will prepend space before newline on the right
// or the end of the buffer, effectively extending it
char moveRight(Lines* buffer_ptr, Head* curr_head_ptr, uint32_t n);

// moveLeft subtracts n from head's pos and returns mod it's standing on
// or EOF if reached newline or the beginning of the buffer,
// however - if destructive, it will insert space after newline on the left
// or the beginning of the buffer, effectively extending it
char moveLeft(Lines* buffer_ptr, Head* curr_head_ptr, uint32_t n);

// moveDown moves the cursor n lines down keeping the same pos_x within a line
// if destructive creates a new line,
// if not destructive, and there's no line already created below, return EOF
char moveDown(Lines* buffer_ptr, Head* curr_head_ptr, uint32_t n);

// moveUp moves the cursor n lines up keeping the same pos_x within a line
// if destructive creates a new line,
// if not destructive, and there's no line already created above, return EOF
char moveUp(Lines* buffer_ptr, Head* curr_head_ptr, uint32_t n);

// INSTEAD OF USING _lineEdgeCounter USE lineBeginning or lineEnd
// _lineEdgeCounter returns how many chars are available between head's pos and
// the beginning or end of the line, depending on the direction set
// will return -1 if out of bounds
int32_t _lineEdgeCounter(
    Lines* buffer_ptr, Head* head_ptr,
    bool direction  // true means lineBeginning, false means lineEnd
);

// lineBeginning returns how many chars are available between head's pos and
// the beginning of the line
#define lineBeginning(LINES_PTR, HEAD_PTR) \
    _lineEdgeCounter(LINES_PTR, HEAD_PTR, true)

// lineEnd returns how many chars are available between head's pos and
// the end of the line
#define lineEnd(LINES_PTR, HEAD_PTR) \
    _lineEdgeCounter(LINES_PTR, HEAD_PTR, false)

// isLegalPosition returns if head_ptr's position is inside the Lines's buffer
bool isLegalPosition(Lines* buffer_ptr, Head* head_ptr);

// writeChar writes head's mod as a char to the buffer and increments it's x_pos
// if it's about to run outside the line - it just extends it
bool writeChar(Lines* buffer_ptr, Head* w_head_ptr);


#endif
