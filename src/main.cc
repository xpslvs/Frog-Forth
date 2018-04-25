
/* main.cc */
#include "forth.hh"

bool forth::running = true;

int main(int argc, char **argv)
{
	forth::init();
	while(forth::running)
	{
		forth::tick();	
	}
	forth::exit();

	return 0;
}

