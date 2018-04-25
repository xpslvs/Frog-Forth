
/* execute.cc */
#include <cstdio>
#include "forth.hh"
#include "parser.hh"
#include "dictionary.hh"
#include "word.hh"

namespace forth
{
	static void execute_procedure(const char *); 

	void execute(void)
	{
		const Word *word = dictionary::search(token);
		if(word)
			execute_word(word);
		else if(parser::token_is_scalar(token))
			stack.push(std::atoi(token));	
		else
			throw std::invalid_argument((std::string)"Word undefined: " + token);
		exec.instruction++;
	}
	
	void execute_word(const Word *word)
	{
		printf("Executing word \"%s\"\n", word->ident);
		switch(word->type)
		{
		case WORD::PRIMITIVE:
			word->value.procedure();
			break;
		case WORD::PROCEDURE:
			execute_procedure(word->value.instruction);	
			break;
		}
	
	}

	static void execute_procedure(const char *address)
	{
		addrstack.push(exec.instructionptr);
		exec.instructionptr = (char *)address;
	}
}

