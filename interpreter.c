#include "interpreter.h"


uint8_t interpret(Lines* buffer_ptr, Head* r_head_ptr, Head* w_head_ptr) {

    bool should_end = false;
    Head* curr_head_ptr = w_head_ptr;

    while ( !should_end ) {

        should_end = execute(
            buffer_ptr, r_head_ptr, w_head_ptr, &curr_head_ptr
        );

        r_head_ptr->pos_x++;
    }

    // returning 0, as in 0 errors
    return 0;
}


bool execute(
    Lines* buffer_ptr,
    Head* r_head_ptr, Head* w_head_ptr, Head** curr_head_ptr
) {
    if ( !isLegalPosition(buffer_ptr, r_head_ptr) ) {
        fprintf(stderr, "Exit from r_head_ptr line overflow\n");
        return true;
    }

    char opcode = buffer_ptr->lines[r_head_ptr->pos_y][r_head_ptr->pos_x];
    char next = '\0';

    // used to make 'x' and 'y' opcodes work
    int to_line = 0;

    // used to make '-' opcode work
    uint32_t mul = 1;

    printf("\nNEXT OPCODE(%i)> \"%c\"\n", r_head_ptr->pos_x, opcode);
    printf("R_POS (%i, %i)\n", r_head_ptr->pos_x, r_head_ptr->pos_y);
    printf("W_POS (%i, %i)\n", w_head_ptr->pos_x, w_head_ptr->pos_y);
    printf("R_MOD(%i)\n", r_head_ptr->mod);
    printf("W_MOD(%i)\n", w_head_ptr->mod);


    switch (opcode) {

        case 'w':
            printf("Switch to w head\n");
            *curr_head_ptr = w_head_ptr;
            break;

        case 'r':
            printf("Switch to r head\n");
            *curr_head_ptr = r_head_ptr;
            break;

        case '\\':
            printf("Go down\n");

            next = moveDown(buffer_ptr, *curr_head_ptr, (*curr_head_ptr)->mod);
            if ( next == EOF ) {
                return true;
            }
            // return true;

            if ( *curr_head_ptr == r_head_ptr ) {
                (*curr_head_ptr)->pos_x--;
            }
            break;

        case '/':
            printf("Go up\n");

            next = moveUp(buffer_ptr, *curr_head_ptr, (*curr_head_ptr)->mod);
            if ( next == EOF ) {
                printf("up oof");
                return true;
            }

            if ( *curr_head_ptr == r_head_ptr ) {
                (*curr_head_ptr)->pos_x--;
            }
            break;

        case '<':
            printf("Go left\n");

            next = moveLeft(buffer_ptr, *curr_head_ptr, (*curr_head_ptr)->mod);
            if ( next == EOF ) {
                return true;
            }

            // subtract from head pos instead of executing recursively
            if ( *curr_head_ptr == r_head_ptr ) {
                (*curr_head_ptr)->pos_x--;
            }

            break;

        case '>':
            printf("Go right\n");

            next = moveRight(buffer_ptr, *curr_head_ptr, (*curr_head_ptr)->mod);
            if ( next == EOF ) {
                return true;
            }

            // subtract from head pos instead of executing recursively
            if ( *curr_head_ptr == r_head_ptr ) {
                (*curr_head_ptr)->pos_x--;
            }

            break;

        case 'y':
            to_line = (*curr_head_ptr)->mod - (*curr_head_ptr)->pos_y;
            if ( to_line < 0 ) {
                next = moveUp(buffer_ptr, *curr_head_ptr, -to_line);
            } else {
                next = moveDown(buffer_ptr, *curr_head_ptr, to_line);
            }

            if ( next == EOF ) {
                return true;
            }

            if ( *curr_head_ptr == r_head_ptr ) {
                (*curr_head_ptr)->pos_x--;
            }

            break;

        case 'x':
            to_line = (*curr_head_ptr)->mod - (*curr_head_ptr)->pos_x;
            if ( to_line < 0 ) {
                next = moveLeft(buffer_ptr, *curr_head_ptr, -to_line);
            } else {
                next = moveRight(buffer_ptr, *curr_head_ptr, to_line);
            }

            if ( next == EOF ) {
                return true;
            }

            if ( *curr_head_ptr == r_head_ptr ) {
                (*curr_head_ptr)->pos_x--;
            }

            break;

        // prints char value of mod
        case '.':
            printf("SCAF> %c\n", w_head_ptr->mod);
            writeChar(buffer_ptr, w_head_ptr);
            break;

        // prints numeric value of mod
        case '=':
            printf("SCAF= %i\n", w_head_ptr->mod);
            // converting numeric mod to a char
            w_head_ptr->mod += 0x30;
            writeChar(buffer_ptr, w_head_ptr);
            break;

        // change mul's value so '+' will subtract
        case '-':
            mul = -1;

            // fall through

        // adds next mod's numerical value to current mod
        case '+':
            next = moveRight(buffer_ptr, r_head_ptr, 1);
            if ( next == EOF ) {
                return true;
            }

            (*curr_head_ptr)->mod += (next-0x30)*mul;
            mul = 1;

            break;

        // ? allows for conditional execution
        // if the field before it is equal to 1 it advances r_head's pos by one
        //
        // if it's not - it decrements the value of the field checked and
        // advances r_head's pos by two
        //
        // if the positioning of ? turns out impossible to decrement the field
        // before it stops the execution
        case '?':
            if ( r_head_ptr->pos_x == 0 ) {
                return true;
            }

            // assigning the value of the field before
            next = buffer_ptr->lines[r_head_ptr->pos_y][r_head_ptr->pos_x-1];

            // the amount r_head is gonna be incremented by
            int amount = 2;

            // performing the check
            if ( next == 1 ) {
                amount = 1;
            } else {
                buffer_ptr->lines[r_head_ptr->pos_y][r_head_ptr->pos_x-1]--;
            }

            next = moveRight(buffer_ptr, r_head_ptr, amount);
            if ( next == EOF ) {
                return true;
            }

            // i mean i gotta do this after every move to make the opcode work
            r_head_ptr->pos_x--;

            break;

        // escape the next character;
        // also allows for chars representing numbers (48-57) to be loaded into
        // mod in their char value
        case ',':
            next = moveRight(buffer_ptr, r_head_ptr, 1);
            if ( next == EOF ) {
                return true;
            }

            (*curr_head_ptr)->mod = next;

            break;

        default:
            printf("Load mod \"%c\"\n", opcode);

            // if the char represents a number, load it's numerical value
            // rather than the char itself
            if ( isNumber(opcode) ) {
                opcode -= 0x30;
            }
            printf("Loaded value (%i)\n", opcode);


            (*curr_head_ptr)->mod = opcode;
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
