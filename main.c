#include <stdio.h>
#include <stdlib.h>

#include "Head.h"
#include "fileHandling.h"
#include "interpreter.h"


int main() {
    Head r_head = genHead();
    Head w_head = genHead();

    FILE* file = fopen("hw.scaf", "r");
        int32_t file_size = getSize(file);
        char* start_ptr = loadFile(file, file_size);
    fclose(file);

    bool success = interpret(start_ptr, file_size, r_head, w_head);

    if ( !success ) {
        printf("Some error occured, fuck off");
    }

    free(start_ptr);
}
