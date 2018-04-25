
/* forth.hh */
#pragma once

#include "stack.hh"
#include "word.hh"

extern Stack<int>    datastack;
extern Stack<char *> addrstack;
extern Stack<int>    stack;
extern Stack<float>  floatstack;

namespace forth
{
	enum MODE : int
	{
		INTERPRET,
		COMPILE,
		EXECUTE,
	};

	struct ExecutionState
	{
		char *instructionptr;
		int   instruction;
		int   mode;
	};
	
	extern ExecutionState exec;
	extern char token[VAR_TOKEN_MAX_LENGTH + 1];
	extern char next [VAR_TOKEN_MAX_LENGTH + 1];
	extern char prev [VAR_TOKEN_MAX_LENGTH + 1];

	void init(void);
	void exit(void);
	void tick(void);
	void run(void);
	void include(const char *);
	void start_compile(void);
	void compile(void);
	void end_compile(void);
	void execute(void);
	void execute_word(const Word *);
}

