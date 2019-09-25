#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// getSize returns file size
uint32_t getSize(FILE* file);

// loadFile loads file into a char buffer
char* loadFile(FILE* file, uint32_t file_size);

// insert inserts char at specified location in the buffer, returns
// pointer to the reallocated buffer (and increments buffer_len ofc),
// or if error occured, returns the same buffer (without incremented len)
char* insert(
    char* buffer_ptr, uint32_t* buffer_len, char c, uint32_t index, uint32_t n
);

// append appends char to the end of the buffer and returns pointer
// to the reallocated one, or to the same one if it fails lol
// ofc it increments buffer_len accordingly
char* append(char* buffer_ptr, uint32_t* buffer_len, char c);


#endif
