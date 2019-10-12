#include <stdio.h>
#include <stdlib.h>

#include "helperFunctions.h"
#include "Head.h"
#include "fileHandling.h"
#include "interpreter.h"
#include "Lines.h"


int run(char* filename, Flags* f) {
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


    // allocating memory for a string+5 in case non_destructive is set
    char* filename_out = malloc(strlen(filename)+5);
    strcpy(filename_out, filename);

    if ( f->output ) {
        free(filename_out);
        filename_out = f->output_filename;
    } else if ( f->non_destructive ) {
        strcat(filename_out, ".out");
    }

    saveToFile(lines_buffer, filename_out);

    if ( !f->output ) {
        free(filename_out);
    }


    freeLines(lines_buffer);

    return error_code;
}


int main(int argc, char** argv) {

    Flags options = parseFlags(argc, argv);

    if ( argc-optind < 1 ) {
        fprintf(stderr, "No input files\n");
        return 1;
    }

    int res = 1;
    for ( uint8_t x = optind; x < argc; x++ ) {

        if ( !verifyPath(argv[x], &options) ) {
            exit(1);
        }

        res = run(argv[x], &options);
        if ( res != 0 ) {
            fprintf(stderr, "Error when interpreting %s\n", argv[x]);
            return res;
        }
    }

    return res;
}
