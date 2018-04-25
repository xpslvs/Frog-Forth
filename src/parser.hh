
/* parser.h */
#pragma once

#include "var.hh"

namespace parser
{
	void *parse_scalar(const char *, int);
	bool  token_is_scalar(const char *);
	bool  streq(const char *, const char *);
	int   token_next(char *, const char *, int);
	char *read_file(const char *);
	int   read_line(char *);	
}

