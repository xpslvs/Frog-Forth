
/* compile.cc */
#include <cstring>
#include <cstdio>
#include "forth.hh"
#include "dictionary.hh"
#include "word.hh"
#include "var.hh"
#include "parser.hh"

namespace forth
{
	static char *startaddr = nullptr;
	static char *endaddr   = nullptr;
	static char name[32];
	static int   words     = 0;
	
	void compile(void)
	{
		if(startaddr == nullptr)
		{
			startaddr = exec.instructionptr;
			strcpy(name, prev);
		}
		++words;
		if(parser::streq(next, ";"))
			exec.mode = MODE::EXECUTE;
	}

	void end_compile(void)
	{
		printf("end_compile()\n");
		char *addr;
		int length;

		endaddr = exec.instructionptr; 
		length  = (int)(endaddr - startaddr);
		addr  	= new char[length+1];
		strncpy(addr, startaddr, length);
		addr[length] = '\0';

		printf("ENDED COMPILE OF PROCEDURE:\n\"%s\"\n\n", addr);
		dictionary::define(WORD::PROCEDURE, name, addr);
		exec.mode = MODE::EXECUTE;
	}
}

