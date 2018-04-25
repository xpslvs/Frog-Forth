
/* stack.cc */
#pragma once

#include <exception>
#include <stdexcept>
#include "stack.hh"

template <class T>
Stack<T>::Stack(int size)
{
	this->base    = new T[size];
	this->pointer = this->base;
	this->memory  = size;
}

template <class T>
Stack<T>::~Stack(void)
{
	delete[] this->base;
}

template <class T>
void Stack<T>::realloc(int size)
{
	T *data = new T[size];
	for(int i = 0; i < this->size(); ++i)
	{
		data[i] = this->base[i];
	}
	
	delete[] this->base;
	this->base    = data;
	this->pointer = this->base;
	this->memory  = size;
}

template <class T>
void Stack<T>::empty(void)
{
	this->pointer = this->base;
}

template <class T>
void Stack<T>::push(const T &x)
{
	if(this->size() >= this->capacity())
		throw std::overflow_error("Stack overflow");
	*(this->pointer++) = x;
}

template <class T>
T Stack<T>::pop(void)
{
	if(this->size() <= 0)
		throw std::underflow_error("Stack underflow");
	return *(--this->pointer);
}

template <class T>
void Stack<T>::pick(unsigned n)
{
	if(this->size() <= n)
		throw std::underflow_error("Stack underflow");
	this->push(this->pointer[-(int)(n+1)]);
}

template <class T>
void Stack<T>::roll(unsigned n)
{
	this->pick(n);
	for(int i = -(int)(n+2); i <= -2; ++i)
	{
		this->pointer[i] = this->pointer[i+1];
	}
	this->drop();
}

template <class T>
T Stack<T>::peek(void) const
{
	const T x = this->pop();
	this->push(x);
	return x;
}

template <class T>
inline void Stack<T>::dup(void)
{
	this->pick(0);
}

template <class T>
inline void Stack<T>::drop(void)
{
	this->pop();
}

template <class T>
inline void Stack<T>::swap(void)
{
	this->roll(1);
}

template <class T>
inline void Stack<T>::over(void)
{
	this->pick(1);
}

template <class T>
inline void Stack<T>::rot(void)
{
	this->roll(2);
}

template <class T>
inline void Stack<T>::nip(void) 
{
	this->swap();
	this->drop();
}

template <class T>
inline void Stack<T>::tuck(void)
{
	this->swap();
	this->over();
}

template <class T>
inline int Stack<T>::size(void) const
{
	return (int)(this->pointer - this->base);
}

template <class T>
inline int Stack<T>::capacity(void) const
{
	return this->memory;
}

