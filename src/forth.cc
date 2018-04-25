
/* forth.cc */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>
#include "forth.hh"
#include "parser.hh"
#include "word.hh"
#include "dictionary.hh"
#include "stack.hh"
#include "primitives.hh"

Stack<int>    datastack(VAR_DATASTACK_ALLOC_SIZE);
Stack<char *> addrstack(VAR_ADDRSTACK_ALLOC_SIZE);
Stack<int>    stack(VAR_STACK_ALLOC_SIZE);
Stack<float>  floatstack(VAR_FLOATSTACK_ALLOC_SIZE);

namespace forth
{
	ExecutionState exec;

	char token[VAR_TOKEN_MAX_LENGTH + 1] = {0};
	char next [VAR_TOKEN_MAX_LENGTH + 1] = {0};
	char prev [VAR_TOKEN_MAX_LENGTH + 1] = {0};
	
	static void next_token(void);
	static void interpret(void);

	void init(void)
	{
		primitives::load();
		exec.instructionptr = nullptr;
		exec.instruction    = 0;
		exec.mode           = MODE::INTERPRET;
	}

	void exit(void)
	{
		dictionary::empty();
	}

	void tick(void)
	{
		try
		{
			next_token();

			switch(exec.mode)
			{
			case MODE::EXECUTE:
				execute();
				break;
			case MODE::COMPILE:
				compile();
				break;
			default:
				interpret();
				break;
			}
		}
		catch(const std::exception &except)
		{
			std::fprintf(stderr, "%s\n", except.what());
			addrstack.empty();
			stack.empty();
			floatstack.empty();
		}
	}

	static void next_token(void)
	{
		static char buffer[VAR_LINE_BUFFER_SIZE] = {0};

		while(exec.instructionptr == nullptr || *exec.instructionptr == '\0')
		{
			std::putchar('$');
			parser::read_line(buffer);
			exec.instructionptr = buffer;
			exec.mode = MODE::EXECUTE;
		}
		
		std::strcpy(prev, token);
		exec.instructionptr += parser::token_next(token, exec.instructionptr, 0);
		parser::token_next(next, exec.instructionptr, 0); 
	}

	static void interpret(void)
	{
		exec.mode = MODE::EXECUTE;
	}
		
	void include(const char *filename)
	{
	
	}
}
	
