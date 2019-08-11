#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "Head.h"


bool interpret(char* buffer_ptr, uint32_t buffer_len, Head r_head, Head w_head);


// execute executes opcode and returns true if the execution should end
bool execute(
    char* buffer_ptr, uint32_t buffer_len, uint32_t index,
    Head r_head, Head w_head
);


#endif
