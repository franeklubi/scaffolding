#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "Head.h"


bool interpret(
    char** buffer_ptr, uint32_t* buffer_len,
    Head* r_head_ptr, Head* w_head_ptr
);


// execute executes opcode and returns true if the execution should end
bool execute(
    char** buffer_ptr, uint32_t* buffer_len,
    Head* r_head_ptr, Head* w_head_ptr, Head* current_head_ptr
);


// isNumber returns true if char represents a number
bool isNumber(char c);


#endif
