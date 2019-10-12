#include "helperFunctions.h"


Flags* parseFlags(int argc, char** argv) {

    Flags* f = malloc(sizeof(Flags));
    f->force = false;
    f->non_destructive = false;
    f->output = false;

    int option_index = 0;
    while ( (option_index = getopt(argc, argv, ":fnho:")) != -1 ) {
        switch (option_index) {
            case 'f':
                f->force = true;
                break;

            case 'n':
                f->non_destructive = true;
                break;

            case 'h':
                fprintf(stderr, HELP_MESSAGE);
                exit(1);

            case 'o':
                f->output = true;
                f->output_filename = optarg;
                break;

            case ':':
                fprintf(stderr, "Flag -%c needs a value\n", optopt);
                exit(1);

            case '?':
                fprintf(stderr, "Unknown flag -%c\n", optopt);
                exit(1);
        }
    }

    return f;
}


bool verifyPath(char* path) {
    if ( !stat(path, &sb) == 0 ) {
        fprintf(stderr, "%s: No such file\n", path);
        return false;
    }
    if ( S_ISDIR(sb.st_mode) ) {
        fprintf(stderr, "%s: Path is a directory\n", path);
        return false;
    }
    if ( !checkExtension(path, ".scaf") ) {
        fprintf(stderr, "%s: File is not .scaf source\n", path);
        return false;
    }

    return true;
}
