#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "Head.h"


uint8_t interpret(Lines* buffer_ptr, Head* r_head_ptr, Head* w_head_ptr);

// execute executes opcode and returns true if the execution should end
bool execute(
    Lines* buffer_ptr,
    Head* r_head_ptr, Head* w_head_ptr, Head** curr_head_ptr
);

// isNumber returns true if char represents a number
bool isNumber(char c);


#endif
