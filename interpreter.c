#include "interpreter.h"


bool interpret(
    char* buffer_ptr, uint32_t buffer_len,
    Head r_head, Head w_head
) {

    bool should_end = false;
    uint32_t index = 0;

    while ( !should_end ) {

        should_end = execute(
            buffer_ptr, buffer_len, index,
            r_head, w_head
        );

        printf("Should end?: %i\n", should_end);

        index++;
    }

    return true;
}


bool execute(
    char* buffer_ptr, uint32_t buffer_len, uint32_t index,
    Head r_head, Head w_head
) {
    if ( index > buffer_len ) {
        return true;
    }

    char opcode = buffer_ptr[index];

    if ( opcode == '\n' ) {
        return true;
    }

    switch (opcode) {

        case 'w':
            printf("Switch to w head\n");
            break;

        case 'r':
            printf("Switch to r head\n");
            break;

        case '\\':
            printf("Go down\n");
            break;

        case '/':
            printf("Go up\n");
            break;

        case '<':
            printf("Go right\n");
            break;

        case '>':
            printf("Go left\n");
            break;

        case '.':
            printf("Print mod\n");
            break;

        default:
            printf("Load mod\n");
            break;
    }

    return false;
}
