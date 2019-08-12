#ifndef HEAD_H
#define HEAD_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    uint32_t pos;
    uint32_t mod;
    bool destructive;
} Head;


// returns filled Head struct
Head genHead();

// moveRight increments head's pos and returns mod it's standing on, however -
// if destructive, it will prepend space before endline or the end of buffer,
// effectively extending it
char moveRight(Head* current_head_ptr, char* buffer_ptr, uint32_t* buffer_len);


#endif
