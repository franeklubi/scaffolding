#include "interpreter.h"


bool interpret(
    char* buffer_ptr, uint32_t* buffer_len,
    Head* r_head_ptr, Head* w_head_ptr
) {

    bool should_end = false;
    Head* current_head_ptr = r_head_ptr;

    while ( !should_end ) {

        should_end = execute(
            buffer_ptr, buffer_len,
            r_head_ptr, w_head_ptr, current_head_ptr
        );

        // printf("Should end?: %i\n", should_end);

        r_head_ptr->pos++;
    }

    return true;
}


bool execute(
    char* buffer_ptr, uint32_t* buffer_len,
    Head* r_head_ptr, Head* w_head_ptr, Head* current_head_ptr
) {
    if ( r_head_ptr->pos >= *buffer_len ) {
        return true;
    }

    char opcode = buffer_ptr[r_head_ptr->pos];
    // printf("current opcode: >%c<\n", opcode);

    if ( opcode == '\n' ) {
        return true;
    }

    switch (opcode) {

        case 'w':
            printf("Switch to w head\n");
            current_head_ptr = w_head_ptr;
            break;

        case 'r':
            printf("Switch to r head\n");
            current_head_ptr = r_head_ptr;
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
            printf("%c", w_head_ptr->mod);
            break;

        case ',':
            r_head_ptr->pos++;

            if ( r_head_ptr->pos >= *buffer_len ) {
                return true;
            }

            w_head_ptr->mod = buffer_ptr[r_head_ptr->pos];
            break;

        default:
            // printf("Load mod\n");
            w_head_ptr->mod = opcode;
            break;
    }

    return false;
}
