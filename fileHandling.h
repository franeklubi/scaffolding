#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H


// getSize returns file size
uint32_t getSize(FILE* file);

// loadFile loads file into a char buffer
char* loadFile(FILE* file, uint32_t file_size);

// inserts char at specified location in the buffer, returns pointer to the
// reallocated buffer
char* insert(char* buffer_ptr, uint32_t* buffer_len, char c, uint32_t index);

#endif
