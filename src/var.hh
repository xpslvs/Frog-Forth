
/* var.hh */
#pragma once

#define VAR_DATASTACK_ALLOC_SIZE  4096
#define VAR_ADDRSTACK_ALLOC_SIZE  2048
#define VAR_STACK_ALLOC_SIZE      1024
#define VAR_FLOATSTACK_ALLOC_SIZE 512 
#define VAR_TOKEN_MAX_LENGTH 31
#define VAR_IDENT_MAX_LENGTH VAR_TOKEN_MAX_LENGTH
#define VAR_LINE_BUFFER_SIZE 256

namespace forth
{
	extern bool running;
}
