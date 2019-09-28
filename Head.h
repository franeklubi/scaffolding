#ifndef HEAD_H
#define HEAD_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "fileHandling.h"


typedef struct {
    uint32_t pos;
    int32_t mod;
    bool destructive;
} Head;


// returns filled Head struct
Head genHead();

// moveRight increments head's pos and returns mod it's standing on or EOF
// if reached newline or the end of the buffer,
// however - if destructive, it will prepend space before newline on the right
// or the end of the buffer, effectively extending it
char moveRight(
    Head* current_head_ptr, char** buffer_ptr, uint32_t* buffer_len
);

// moveLeft subtracts n from head's pos and returns mod it's standing on
// or EOF if reached newline or the beginning of the buffer,
// however - if destructive, it will insert space after newline on the left
// or the beginning of the buffer, effectively extending it
char moveLeft(
    Head* current_head_ptr, char** buffer_ptr, uint32_t* buffer_len, uint32_t n
);

// lineBeginning returns how many chars are available between head's pos and
// the beginning of the line
uint32_t lineBeginning(
    Head* current_head_ptr, char** buffer_ptr, uint32_t* buffer_len
);

// lineEnd returns how many chars are available between head's pos and
// the end of the line
uint32_t lineEnd(
    Head* current_head_ptr, char** buffer_ptr, uint32_t* buffer_len
);


#endif
