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
        #ifdef _DEBUG
            fprintf(stderr, "Error with creating lines_buffer\n");
        #endif
        return 1;
    }


    #ifdef _DEBUG
        fprintf(stderr, "First buffer draw:\n");
        printToStderr(lines_buffer);
        fprintf(stderr, "\n");
    #endif

    uint8_t error_code = interpret(lines_buffer, &r_head, &w_head);

    #ifdef _DEBUG
        fprintf(stderr, "\nLast buffer draw:\n");
        printToStderr(lines_buffer);
        fprintf(stderr, "\n");
    #endif


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
