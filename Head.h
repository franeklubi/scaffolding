#ifndef HEAD_H
#define HEAD_H

#include <stdint.h>


typedef struct {
    uint32_t x;
    uint32_t y;
    char op;
    uint32_t mod;
} Head;


Head genHead();


#endif
