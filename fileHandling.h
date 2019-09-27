#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// getSize returns file size
uint32_t getSize(FILE* file);

// loadFile loads file into a char buffer
char* loadFile(FILE* file, uint32_t file_size);

// insert inserts n chars at specified location in the buffer,
// returns true if the operation was successful, false otherwise
bool insert(
    char** buffer_ptr, uint32_t* buffer_len, char c, uint32_t index, uint32_t n
);

// append appends n chars to the end of the buffer,
// returns true if the operation was successful, false otherwise
bool append(char** buffer_ptr, uint32_t* buffer_len, char c, uint32_t n);


#endif
