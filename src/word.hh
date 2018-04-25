
/* word.hh */
#pragma once

#include "var.hh"

enum WORD : int
{
	PRIMITIVE, /* Implemented as a C function */
	PROCEDURE, /* Implemented as a Forth procedure/word */
	VARIABLE,
	CONSTANT
};

union WordValue
{
	void    (*procedure)(void);
	char     *instruction;
	void     *address;
	int       word;
	long long dword;
	float     floatp;
};

struct Word
{
public:
	WordValue value;
	int       type;
	int       hash;
	char      ident[VAR_IDENT_MAX_LENGTH + 1];

	Word(void) {}
	Word(int, const char *, void (*)(void));
	Word(int, const char *, char *);
	Word(int, const char *, int);
	Word(int, const char *, long long);
	Word(int, const char *, float);
private:
	void set(int, const char *);
};

