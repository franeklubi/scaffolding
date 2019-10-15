#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "Head.h"


typedef struct {
    Lines* buffer_ptr;
    Head* r_head_ptr;
    Head* w_head_ptr;
    Head* curr_head_ptr;
} ProgramState;


// genProgramState generates program state
ProgramState genProgramState(
    Lines* buffer_ptr, Head* r_head_ptr, Head* w_head_ptr
);

// interpret uses execute to run the program till
// execute thinks it's time to stop
uint8_t interpret(ProgramState* state);

// execute executes opcode and returns true if the execution should end
bool execute(ProgramState* state);

// isNumber returns true if char represents a number
bool isNumber(char c);


#endif
