#ifndef LINES_H
#define LINES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    char** lines;
    int32_t no_lines;
    uint32_t* lines_len;
} Lines;


// dissectLines dissects buffer of chars into separate lines
// and stores them along with other information in struct Lines
Lines* dissectLines(char* buffer_ptr, uint32_t buffer_len);

// freeLines frees allocated memory in Lines* struct
void freeLines(Lines* lines_ptr);

// insertLines inserts line_n of emmpty lines in lines_ptr
// initializes each line with n of empty characters
bool insertLines(Lines* lines_ptr, uint32_t index, uint32_t line_n, uint32_t n);


#endif
