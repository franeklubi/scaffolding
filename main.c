#include <stdio.h>
#include <stdlib.h>

#include "Head.h"
#include "fileHandling.h"
#include "interpreter.h"


int main() {
    // Head r_head = genHead();
    // Head w_head = genHead();
    // w_head.destructive = true;

    FILE* file = fopen("down.scaf", "r");
        uint32_t file_size = getSize(file);
        char* start_ptr = loadFile(file, file_size);
    fclose(file);

    Lines* lines_buffer = dissectLines(start_ptr, file_size);
    free(start_ptr);
    if ( !lines_buffer ) {
        fprintf(stderr, "Error with creating lines_buffer\n");
        return 1;
    }

    for ( int x = 0; x < lines_buffer->no_lines; x++ ) {
        // printf("LINE %i LEN> %i\n", x, lines_buffer->lines_len[x]);
        for ( int y = 0; y < lines_buffer->lines_len[x]; y++ ) {
            printf("%c", lines_buffer->lines[x][y]);
        }
        printf("\n");
    }

    freeLines(lines_buffer);

    // printf("\nFirst buffer draw: (%i)\n", file_size);
    // for ( uint32_t x = 0; x < file_size; x++ ) {
    //     printf("%i> \"%c\"\n", x, start_ptr[x]);
    // }
    // printf("\n");
    //
    //
    // // printf("execution:\n");
    //
    // bool error_code = interpret(&start_ptr, &file_size, &r_head, &w_head);
    //
    //
    // printf("\nLast buffer draw: (%i)\n", file_size);
    // for ( uint32_t x = 0; x < file_size; x++ ) {
    //     printf("%i> \"%c\"\n", x, start_ptr[x]);
    // }
    // printf("\n");


    // return error_code;
    return 0;
}
