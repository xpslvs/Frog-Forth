
/* word.cc */
#include <cstring>
#include "word.hh"
#include "var.hh"

Word::Word(int type, const char *ident, void (*procedure)(void))
{
	this->set(type, ident);
	this->value.procedure = procedure;
}

Word::Word(int type, const char *ident, char *instruction)
{
	this->set(type, ident);
	this->value.instruction = instruction;
}

Word::Word(int type, const char *ident, int word)
{
	this->set(type, ident);
	this->value.word = word;
}

Word::Word(int type, const char *ident, long long dword)
{
	this->set(type, ident);
	this->value.dword = dword;
}

Word::Word(int type, const char *ident, float floatp)
{
	this->set(type, ident);
	this->value.floatp = floatp;
}

void Word::set(int type, const char *ident)
{
	this->type = type;
	int length = std::strlen(ident);
	if(length >= VAR_IDENT_MAX_LENGTH)
		length = VAR_IDENT_MAX_LENGTH;
	std::strncpy(this->ident, ident, length);
	this->ident[length] = '\0';
}

