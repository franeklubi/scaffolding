#ifndef HEAD_H
#define HEAD_H

#include <stdint.h>


typedef struct {
    uint32_t pos;
    char mod;
} Head;


Head genHead();


#endif
