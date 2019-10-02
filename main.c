#include <stdio.h>
#include <stdlib.h>

#include "Head.h"
#include "fileHandling.h"
#include "interpreter.h"
#include "Lines.h"


int main() {
    Head r_head = genHead();
    Head w_head = genHead();
    w_head.destructive = true;

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

    printf("\nFirst buffer draw:\n");
    for ( int x = 0; x < lines_buffer->no_lines; x++ ) {
        printf("LINE(%x) LEN(%x)> \"", x, lines_buffer->lines_len[x]);
        for ( int y = 0; y < lines_buffer->lines_len[x]; y++ ) {
            printf("%c", lines_buffer->lines[x][y]);
        }
        printf("\"\n");
    }


    uint8_t error_code = interpret(lines_buffer, &r_head, &w_head);


    freeLines(lines_buffer);

    return error_code;
}
