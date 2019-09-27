#include <stdio.h>
#include <stdlib.h>

#include "Head.h"
#include "fileHandling.h"
#include "interpreter.h"


int main() {
    Head r_head = genHead();
    Head w_head = genHead();
    w_head.destructive = true;

    FILE* file = fopen("loop.scaf", "r");
        uint32_t file_size = getSize(file);
        char* start_ptr = loadFile(file, file_size);
    fclose(file);


    printf("\nFirst buffer draw: (%i)\n", file_size);
    for ( uint32_t x = 0; x < file_size; x++ ) {
        printf("%i> \"%c\"\n", x, start_ptr[x]);
    }


    printf("\nexecution:\n");

    bool error_code = interpret(&start_ptr, &file_size, &r_head, &w_head);

    printf("\nLast buffer draw: (%i)\n", file_size);
    for ( uint32_t x = 0; x < file_size; x++ ) {
        printf("%i> \"%c\"\n", x, start_ptr[x]);
    }
    printf("\n");

    free(start_ptr);


    return error_code;
}
