#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <stdbool.h>
#include <sys/stat.h>
#include <stdio.h>
#include <getopt.h>

#include "fileHandling.h"


#define HELP_MESSAGE "\
Usage: scaf [options] file...\n\n\
Optional arguments:\n\
  -f\t\tDon't check if file is a scaf source.\n\
  -n\t\tOutput to filename.out (Don't overwrite file).\n\
  -o <path>\tOutput to <path>.\n\
  -h\t\tDisplay this help message.\n\
"


// struct needed for sys/stat
struct stat sb;

// struct containing all the switches controlled by flags
typedef struct {
    bool force;
    bool non_destructive;
    bool output;
    char* output_filename;
} Flags;


// parseFlags does exactly what you think
Flags parseFlags(int argc, char** argv);

// verifyPath checks if path exists, is not a directory, and is a .scaf source
bool verifyPath(char* path);


#endif
