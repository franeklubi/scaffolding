#include "interpreter.h"


bool interpret(
    char** buffer_ptr, uint32_t* buffer_len,
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

    // returning 0, as in 0 errors
    return 0;
}


bool execute(
    char** buffer_ptr, uint32_t* buffer_len,
    Head* r_head_ptr, Head* w_head_ptr, Head* current_head_ptr
) {
    if ( r_head_ptr->pos >= *buffer_len ) {
        return true;
    }

    char opcode = (*buffer_ptr)[r_head_ptr->pos];
    char next = '\0';
    uint32_t mul = 1;
    // printf("current opcode: [%c], index[%i]\n", opcode, r_head_ptr->pos);

    if ( opcode == '\n' ) {
        printf("NEXT OPCODE(%i)> NEWLINE\n", r_head_ptr->pos);
    } else {
        printf("NEXT OPCODE(%i)> \"%c\"\n", r_head_ptr->pos, opcode);
    }

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

            next = moveLeft(
                current_head_ptr, buffer_ptr, buffer_len, w_head_ptr->mod
            );
            if ( next == EOF ) {
                return true;
            }

            // subtract from head pos instead of executing recursively
            current_head_ptr->pos--;

            break;

        case '>':
            printf("Go right\n");

            next = moveRight(
                current_head_ptr, buffer_ptr, buffer_len, w_head_ptr->mod
            );
            if ( next == EOF ) {
                return true;
            }

            // subtract from head pos instead of executing recursively
            current_head_ptr->pos--;

            break;

        // prints char value of mod
        case '.':
            printf("SCAF> %c\n", w_head_ptr->mod);
            break;

        // prints numeric value of mod
        case '=':
            printf("SCAF= %i\n", w_head_ptr->mod);
            break;

        // change mul's value so '+' will subtract
        case '-':
            mul = -1;

        // adds next mod's numerical value to current mod
        case '+':
            next = moveRight(r_head_ptr, buffer_ptr, buffer_len, 1);
            if ( next == EOF ) {
                return true;
            }

            w_head_ptr->mod += (next-0x30)*mul;
            mul = 1;
            break;

        // if w_head_ptr's mod value is -ne 0 act as opcode ',',
        // it also decrements value of buffer_ptr[r_head_ptr->pos-1]
        // but if /decrementage/ turns out impossible
        // it just fucks the whole thing up, so be wary where you put '?'
        case '?':
            next = *buffer_ptr[r_head_ptr->pos-1];
            if ( r_head_ptr->pos == 0 || next == '\n' ) {
                return true;
            }

            // decrementing the index before
            if ( w_head_ptr->mod == 0 ) {
                break;
            } else {
                buffer_ptr[r_head_ptr->pos-1]--;
            }

        // escape the next character;
        // also allows for chars representing numbers (48-57) to be loaded into
        // mod in their char value
        case ',':
            next = moveRight(r_head_ptr, buffer_ptr, buffer_len, 1);
            if ( next == EOF ) {
                return true;
            }

            w_head_ptr->mod = next;
            break;

        default:
            printf("Load mod \"%c\"\n", opcode);

            // if the char represents a number, load it's numerical value
            // rather than the char itself
            if ( isNumber(opcode) ) {
                opcode -= 0x30;
            }
            w_head_ptr->mod = opcode;
            break;
    }

    return false;
}


bool isNumber(char c) {
    if ( c > 47 && c < 58 ) {
        return true;
    }
    return false;
}
