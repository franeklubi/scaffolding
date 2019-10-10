#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "Head.h"
#include "fileHandling.h"
#include "interpreter.h"
#include "Lines.h"


int run(char* filename) {
    Head r_head = genHead();
    Head w_head = genHead();
    w_head.destructive = true;

    FILE* file = fopen(filename, "r");
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
    printf("\n");

    uint8_t error_code = interpret(lines_buffer, &r_head, &w_head);

    printf("\n");
    printf("\nLast buffer draw:\n");
    for ( int x = 0; x < lines_buffer->no_lines; x++ ) {
        printf("LINE(%x) LEN(%x)> \"", x, lines_buffer->lines_len[x]);
        for ( int y = 0; y < lines_buffer->lines_len[x]; y++ ) {
            printf("%c", lines_buffer->lines[x][y]);
        }
        printf("\"\n");
    }

    freeLines(lines_buffer);

    return error_code;
}


int main(int argc, char** argv) {


    if ( argc < 2 ) {
        fprintf(stderr, "No input files\n");
        return 1;
    }

    struct stat sb;

    int res = 1;
    for ( uint8_t x = 1; x < argc; x++ ) {
        if ( !stat(argv[x], &sb) == 0 ) {
            fprintf(stderr, "%s: No such file\n", argv[x]);
            break;
        }
        if ( S_ISDIR(sb.st_mode) ) {
            fprintf(stderr, "%s: Path is a directory\n", argv[x]);
            break;
        }
        if ( !checkExtension(argv[x], ".scaf") ) {
            fprintf(stderr, "%s: File is not .scaf source\n", argv[x]);
            break;
        }

        res = run(argv[x]);
        if ( res != 0 ) {
            fprintf(stderr, "Error when interpreting %s\n", argv[x]);
            return res;
        }
    }

    return res;
}
