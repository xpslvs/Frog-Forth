
/* parser.cc */
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <exception>
#include <stdexcept>
#include "parser.hh"

namespace parser
{
	bool token_is_scalar(const char *token)
	{
		while(*token)	
		{
			if(!std::isdigit(*token++))
				return false;
		}
		return true;
	}
	
	bool streq(const char *x, const char *y)
	{
		while(*x || *y)
		{
			if(std::toupper(*x++) != std::toupper(*y++))
				return false;
		}
		return true;
	}
	
	/* Assumes buffer has at least PARSER_TOKEN_MAX_LENGTH + 1 slots
	 */
	int token_next(char *buffer, const char *source, int index)
	{
		int length, start, p = index;
		// Skip leading spaces
		while(std::isspace(source[index]) && source[index] != '\n')
		{
			++index;
		}
		start = index;
		while(!std::isspace(source[index]) && source[index] != '\0')
		{
			++index;
		}
		length = index - start;
		if(length > VAR_TOKEN_MAX_LENGTH)
			length = VAR_TOKEN_MAX_LENGTH;
		std::strncpy(buffer, &source[start], length);
		buffer[length] = '\0';
	
		return index - p;
	}
	
	/* Assumes filename exists, the returned buffer needs to be freed with 
	 * free() after use
	 */
	char *read_file(const char *filename)
	{
		FILE *fp;
		char *buffer;
		int length;
	
		fp = std::fopen(filename, "rb");
		if(fp == NULL)
			throw std::invalid_argument((std::string)"File not found: " + filename);	
		std::fseek(fp, 0L, SEEK_END);
		length = std::ftell(fp);
		std::rewind(fp);
		buffer = new char[length + 1];
		std::fread(buffer, sizeof(char), length, fp);
		buffer[length] = '\0';
	
		std::fclose(fp);
		return buffer;
	}
	
	/* Assumes buffer has atleast VAR_LINE_BUFFER_SIZE elements 
	 */
	int read_line(char *buffer)
	{
		if(std::fgets(buffer, VAR_LINE_BUFFER_SIZE, stdin) == NULL)
			return 0;
		char *ptr = buffer;
		// Replace the terminating newline with a null terminator
		while(*buffer != '\n')
			++buffer;
		*buffer = '\0';
	
		return (int)(buffer - ptr);
	}
}
	
