#include "interpreter.h"


bool interpret(
    char* buffer_ptr, uint32_t* buffer_len,
    Head* r_head_ptr, Head* w_head_ptr
) {

    bool should_end = false;
    uint32_t index = r_head_ptr->pos;
    Head* current_head_ptr = r_head_ptr;

    while ( !should_end ) {

        should_end = execute(
            buffer_ptr, buffer_len, &index,
            r_head_ptr, w_head_ptr, current_head_ptr
        );

        // printf("Should end?: %i\n", should_end);

        index++;
    }

    return true;
}


bool execute(
    char* buffer_ptr, uint32_t* buffer_len, uint32_t* index,
    Head* r_head_ptr, Head* w_head_ptr, Head* current_head_ptr
) {
    if ( *index > *buffer_len ) {
        return true;
    }

    char opcode = buffer_ptr[*index];
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
            (*index)++;
            w_head_ptr->mod = buffer_ptr[*index];
            break;

        default:
            // printf("Load mod\n");
            w_head_ptr->mod = opcode;
            break;
    }

    return false;
}
