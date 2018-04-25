
/* stack.c */
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include "stack.h"
#include "error.h"
#include <stdio.h> // Remove

static bool push_overflow(const Stack *);
static bool pop_underflow(const Stack *);

Stack stack_data;
Stack stack_addr;
Stack stack_arg;
Stack stack_float;

void stack_cons(int size, Stack *stack)
{
	stack->bottom = malloc(size);
	if(stack->bottom == NULL)
		error_throw(ERROR_MALLOC);

	stack->memory          = size;	
	stack->pointer         = stack->bottom;
	*(int *)stack->pointer = 0;
}

void stack_delete(Stack *stack)
{
	free(stack->bottom);
	stack->bottom  = NULL;
	stack->pointer = NULL;
	stack->memory  = 0;
}

void stack_reset(Stack *stack)
{
	int size = stack->memory;
	stack_delete(stack);
	stack_cons(size, stack);
}

void stack_push_single(int word, Stack *stack)
{
	printf("Attempting to push %d onto the stack\n", word);
	if(push_overflow(stack))
		error_throw(ERROR_STACK_OVERFLOW);
	else
		*((int *)stack->pointer++) = word; 
}

void stack_push_double(long long dword, Stack *stack)
{
	int high = (int)((dword >> 32) & (int)(~0x00));
	int low  = (int)(dword & (int)(~0x00)); 
	stack_push_single(high, stack);
	stack_push_single(low, stack);
}

int stack_pop_single(Stack *stack)
{
	if(pop_underflow(stack))
		return error_throw(ERROR_STACK_UNDERFLOW), 0;
	else
		return *(int *)(--stack->pointer);
}

long long stack_pop_double(Stack *stack)
{
	long long dword = 0L;
	dword |= stack_pop_single(stack);
	dword |= (long long)(stack_pop_single(stack)) << 32;
	return dword;
}

int stack_size(const Stack *stack)
{
	return (int)(stack->pointer - stack->bottom);
}

/* Checks if a push/pop will cause the stack to over-/underflow
 */
static bool push_overflow(const Stack *stack)
{
	return stack_size(stack) >= stack->memory;
}

static bool pop_underflow(const Stack *stack)
{
	return stack_size(stack) <= 0;
}

