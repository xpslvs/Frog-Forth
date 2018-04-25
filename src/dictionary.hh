
/* dictionary.hh */
#pragma once

#include "word.hh"

namespace dictionary
{
	void     define(int, const char *, ...);
	void     undefine(const char *);
	void     empty(void);
	unsigned size(void);
	Word    *search(const char *);
}
	
