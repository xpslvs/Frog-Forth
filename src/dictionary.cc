
/* dictionary.cc */

#include <cstdarg>
#include "dictionary.hh"
#include "word.hh"
#include "parser.hh"

namespace dictionary
{
	struct Node 
	{
		Node *next;
		Word  word;

		Node(void) {};
	};
	
	static Node *dictionary = nullptr;
	
	void define(int type, const char *ident, ...)
	{
		va_list argv;
		va_start(argv, ident);

		Node *node = new Node;
		node->next = dictionary;
		switch(type)
		{
		case WORD::PRIMITIVE:
			node->word = Word(type, ident, va_arg(argv, void (*)(void)));
			break;
		case WORD::PROCEDURE:
			node->word = Word(type, ident, va_arg(argv, char *));
			break;
		case WORD::VARIABLE:
		case WORD::CONSTANT:
			node->word = Word(type, ident, va_arg(argv, int));
			break;
		default:
			node->word = Word(type, ident, (char *)0);
		}
		dictionary = node;

		va_end(argv);
	}
	
	void undefine(const char *ident)
	{
		Node *node  = dictionary;
		Node *prev  = nullptr;
	
		while(node != nullptr)
		{
			if(parser::streq(node->word.ident, ident))
			{
				Node *next = node->next;
				delete node;	
				if(prev)
					prev->next = next;
				return;
			}
			prev = node;
			node = node->next;
		}
	}
	
	void empty(void)
	{
		Node *node = dictionary;
		while(node != nullptr)
		{
			Node *next = node->next;
			delete node;
			node = next;
		}
	}
	
	unsigned size(void)
	{
		unsigned n = 0;
		Node *node = dictionary;
		while(node != nullptr)
		{
			++n;
			node = node->next;
		}
		return n;
	}
	
	Word *search(const char *ident)
	{
		Node *node = dictionary;
		while(node != nullptr)
		{
			if(parser::streq(node->word.ident, ident))
				return &node->word;
			node = node->next;
		}
		return nullptr;
	}
}
	
