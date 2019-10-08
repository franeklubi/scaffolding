#include "interpreter.h"


uint8_t interpret(Lines* buffer_ptr, Head* r_head_ptr, Head* w_head_ptr) {

    bool should_end = false;
    Head* curr_head_ptr = w_head_ptr;

    while ( !should_end ) {

        should_end = execute(
            buffer_ptr, r_head_ptr, w_head_ptr, curr_head_ptr
        );

        r_head_ptr->pos_x++;
    }

    // returning 0, as in 0 errors
    return 0;
}


bool execute(
    Lines* buffer_ptr,
    Head* r_head_ptr, Head* w_head_ptr, Head* curr_head_ptr
) {
    if ( !isLegalPosition(buffer_ptr, curr_head_ptr) ) {
        return true;
    }

    char opcode = buffer_ptr->lines[r_head_ptr->pos_y][r_head_ptr->pos_x];
    char next = '\0';
    uint32_t mul = 1;

    printf("NEXT OPCODE(%i)> \"%c\"\n", r_head_ptr->pos_x, opcode);


    switch (opcode) {

        case 'w':
            printf("Switch to w head\n");
            curr_head_ptr = w_head_ptr;
            break;

        case 'r':
            printf("Switch to r head\n");
            curr_head_ptr = r_head_ptr;
            break;

        case '\\':
            printf("Go down\n");

            next = moveDown(buffer_ptr, curr_head_ptr, w_head_ptr->mod);
            if ( next == EOF ) {
                return true;
            }

            curr_head_ptr->pos_x--;
            break;

        case '/':
            printf("Go up\n");

            next = moveUp(buffer_ptr, curr_head_ptr, w_head_ptr->mod);
            if ( next == EOF ) {
                printf("up oof");
                return true;
            }

            curr_head_ptr->pos_x--;
            break;

        case '<':
            printf("Go left\n");

            next = moveLeft(buffer_ptr, curr_head_ptr, w_head_ptr->mod);
            if ( next == EOF ) {
                return true;
            }

            // subtract from head pos instead of executing recursively
            curr_head_ptr->pos_x--;

            break;

        case '>':
            printf("Go right\n");

            next = moveRight(buffer_ptr, curr_head_ptr, w_head_ptr->mod);
            if ( next == EOF ) {
                return true;
            }

            // subtract from head pos instead of executing recursively
            curr_head_ptr->pos_x--;

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
            next = moveRight(buffer_ptr, r_head_ptr, w_head_ptr->mod);
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
            if ( r_head_ptr->pos_x == 0 ) {
                return true;
            }
            next = buffer_ptr->lines[r_head_ptr->pos_y][r_head_ptr->pos_x-1];

            // decrementing the index before
            if ( w_head_ptr->mod == 0 ) {
                break;
            } else {
                buffer_ptr->lines[r_head_ptr->pos_y][r_head_ptr->pos_x-1]--;
            }

        // escape the next character;
        // also allows for chars representing numbers (48-57) to be loaded into
        // mod in their char value
        case ',':
            next = moveRight(buffer_ptr, curr_head_ptr, 1);
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
