#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>
#include <stdint.h>

#include "Head.h"


bool interpret(char* buffer_ptr, uint32_t buffer_len, Head r_head, Head w_head);


#endif
