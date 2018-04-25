
/* stack.h */
#pragma once

#if defined(__x86_64__) || defined(__WIN64)
# define stack_push_addr stack_push_double
# define stack_pop_addr  stack_pop_double
#elif defined(__x86__)  || defined(__WIN32)
# define stack_push_addr stack_push_single
# define stack_pop_addr  stack_pop_single
#else
# error "Error determining whether 32 or 64 bit address size"
#endif

#define stack_push stack_push_single
#define stack_pop  stack_pop_single

struct STACK
{
	void *bottom;
	void *pointer;
	int   memory;
};

typedef struct STACK Stack;

extern Stack stack_addr;
extern Stack stack_arg;
extern Stack stack_float;
extern Stack stack_data;

void  stack_cons(int, Stack *);
void  stack_delete(Stack *);
void  stack_reset(Stack *);
void  stack_push_single(int, Stack *);
int   stack_pop_single(Stack *);
void  stack_push_double(long long, Stack *);
long long stack_pop_double(Stack *);
void  stack_push_float(float, Stack *);
float stack_pop_float(Stack *);
int   stack_size(Stack const *);

