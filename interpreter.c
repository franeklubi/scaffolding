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
    char next = '\0';
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
            printf("Go left\n");
            break;

        case '>':
            printf("Go right\n");
            moveRight(current_head_ptr, buffer_ptr, buffer_len);
            break;

        // prints char value of mod
        case '.':
            printf("%c", w_head_ptr->mod);
            break;

        // prints numeric value of mod
        case '=':
            printf("%i", w_head_ptr->mod);
            break;

        // adds next mod's numerical value to current mod's numerical value
        case '+':
            next = moveRight(r_head_ptr, buffer_ptr, buffer_len);

            if ( next == EOF ) {
                return true;
            }

            w_head_ptr->mod -= 0x30;
            w_head_ptr->mod += (next-0x30);
            break;


        case ',':
            next = moveRight(r_head_ptr, buffer_ptr, buffer_len);

            if ( next == EOF ) {
                return true;
            }

            w_head_ptr->mod = next;
            break;

        default:
            // printf("Load mod\n");
            w_head_ptr->mod = opcode;
            break;
    }

    return false;
}
