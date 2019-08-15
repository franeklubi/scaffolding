#include <stdio.h>
#include <stdlib.h>

#include "Head.h"
#include "fileHandling.h"
#include "interpreter.h"


int main() {
    Head r_head = genHead();
    Head w_head = genHead();
    w_head.destructive = true;

    FILE* file = fopen("hw.scaf", "r");
        uint32_t file_size = getSize(file);
        char* start_ptr = loadFile(file, file_size);
    fclose(file);

    for ( uint8_t x = 0; x < file_size; x++ ) {
        printf("%c", start_ptr[x]);
    }
    printf("\n");
    start_ptr = insert(start_ptr, &file_size, '.', 1);
    start_ptr = insert(start_ptr, &file_size, 'O', 1);
    start_ptr = append(start_ptr, &file_size, 'c');
    start_ptr = append(start_ptr, &file_size, '.');
    start_ptr = prepend(start_ptr, &file_size, '.');
    start_ptr = prepend(start_ptr, &file_size, 'W');
    for ( uint8_t x = 0; x < file_size; x++ ) {
        printf("%c", start_ptr[x]);
    }
    printf("\nexecution:\n");

    bool success = interpret(start_ptr, &file_size, &r_head, &w_head);

    if ( !success ) {
        printf("Some error occured, fuck off\n");
    }

    free(start_ptr);
}
