
/* primitives.cc */
#include <cstdio>
#include "primitives.hh"
#include "dictionary.hh"
#include "word.hh"
#include "stack.hh"
#include "forth.hh"

namespace primitives
{
	void _exit(void)
	{
		forth::running = false;
	}

	void _compile(void)
	{
		forth::exec.mode = forth::MODE::COMPILE;
	}

	void _interpret(void)
	{
		forth::exec.mode = forth::MODE::INTERPRET;
	}

	void _execute(void)
	{
		forth::exec.mode = forth::MODE::EXECUTE;
	}

	void _return(void)
	{
		if(addrstack.size() == 0)
			forth::end_compile();
		else
			forth::exec.instructionptr = addrstack.pop();
	}

	void _page(void)
	{
		for(int y = 0; y < 24; ++y)
		{
			for(int x = 0; x < 8; ++x)
			{
				putchar(' ');
			}
			putchar('\n');
		}
	}

	void _pick(void)
	{
		stack.pick(stack.pop());
	}

	void _roll(void)
	{
		stack.roll(stack.pop());
	}

	void _dup(void)
	{
		stack.dup();
	}

	void _drop(void)
	{
		stack.drop();
	}

	void _swap(void)
	{
		stack.swap();
	}

	void _over(void)
	{
		stack.over();
	}

	void _rot(void)
	{
		stack.rot();
	}

	void _nip(void)
	{
		stack.nip();
	}

	void _tuck(void)
	{
		stack.tuck();
	}
	
	void _and(void)
	{
		stack.push(stack.pop() & stack.pop());	
	}

	void _or(void)
	{
		stack.push(stack.pop() | stack.pop());
	}

	void _not(void)
	{
		stack.push(~stack.pop());
	}
	
	void _xor(void)
	{
		stack.push(stack.pop() ^ stack.pop());
	}
	
	void _add(void)
	{
		stack.push(stack.pop() + stack.pop());
	}
	
	void _sub(void)
	{
		stack.push(stack.pop() - stack.pop());
	}
	
	void _mul(void)
	{
		stack.push(stack.pop() * stack.pop());
	}
	
	void _div(void)
	{
		stack.push(stack.pop() / stack.pop());
	}
	
	void _mod(void)
	{
		stack.push(stack.pop() % stack.pop());
	}
	
	void _emit(void)
	{
		std::putchar(stack.pop());
	}
	
	void _dot(void)
	{
		std::printf("%d ", stack.pop());
	}
	
	void _dotstack(void)
	{
		std::putchar('{');
		for(int i = 7 > stack.size()-1 ? stack.size()-1 : 7; i >= 0; --i)
		{
			stack.pick(i);
			std::printf(" %d", stack.pop());
		}
		std::printf(" }\n");
	}
	
	/* Load all the primitive words into the dictionary
	 */
	void load(void)
	{
		dictionary::define(WORD::PRIMITIVE, "EXIT", _exit);
		dictionary::define(WORD::PRIMITIVE, ":", _compile);
		dictionary::define(WORD::PRIMITIVE, "INTERPRET", _interpret);
		dictionary::define(WORD::PRIMITIVE, "EXECUTE", _execute);
		dictionary::define(WORD::PRIMITIVE, ";", _return);
		dictionary::define(WORD::PRIMITIVE, "PAGE", _page);
		dictionary::define(WORD::PRIMITIVE, "PICK", _pick);
		dictionary::define(WORD::PRIMITIVE, "ROLL", _roll);
		dictionary::define(WORD::PRIMITIVE, "DUP", _dup);
		dictionary::define(WORD::PRIMITIVE, "DROP", _drop);
		dictionary::define(WORD::PRIMITIVE, "SWAP", _swap);
		dictionary::define(WORD::PRIMITIVE, "OVER", _over);
		dictionary::define(WORD::PRIMITIVE, "ROT", _rot);
		dictionary::define(WORD::PRIMITIVE, "NIP", _nip);
		dictionary::define(WORD::PRIMITIVE, "TUCK", _tuck);
		dictionary::define(WORD::PRIMITIVE, "AND", _and);
		dictionary::define(WORD::PRIMITIVE, "OR", _or);
		dictionary::define(WORD::PRIMITIVE, "NOT", _not);
		dictionary::define(WORD::PRIMITIVE, "XOR", _xor);
		dictionary::define(WORD::PRIMITIVE, "+", _add);
		dictionary::define(WORD::PRIMITIVE, "-", _sub);
		dictionary::define(WORD::PRIMITIVE, "*", _mul);
		dictionary::define(WORD::PRIMITIVE, "/", _div);
		dictionary::define(WORD::PRIMITIVE, "MOD", _mod);
		dictionary::define(WORD::PRIMITIVE, "EMIT", _emit);
		dictionary::define(WORD::PRIMITIVE, ".", _dot);
		dictionary::define(WORD::PRIMITIVE, ".S", _dotstack);
	}
}

