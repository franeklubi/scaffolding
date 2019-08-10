#ifndef HEAD_H
#define HEAD_H

#include <stdint.h>


typedef struct {
    uint64_t x;
    uint64_t y;
    char op;
    uint64_t mod;
} Head;


Head genHead();


#endif
