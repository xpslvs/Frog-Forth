
/* stack.hh */
#ifndef _STACK_HH_
#define _STACK_HH_

#include <cstring>
#include <exception>
#include <stdexcept>

template <typename T>
class Stack
{
public:
	Stack(unsigned size)
	{
		this->_base = nullptr;
		this->allocate(size);
	}
	
	Stack(const Stack &stack)
	{
		*this = stack.copy();
	}

	~Stack(void)
	{
		delete[] this->_base;
	}
	
	Stack copy(void) const
	{
		Stack stack(this->capacity());
		std::memcpy(stack._base, this->_base, this->capacity() * sizeof(T));
	}

	void allocate(unsigned size)
	{
		if(this->_base != nullptr)
		{
			T *base = new T[size];
			std::memcpy(base, this->_base, this->_capacity * sizeof(T));
			delete[] this->_base;
		}
		this->_base     = base;
		this->_pointer  = this->_base;
		this->_capacity = size;
	}
	
	void clear(void)
	{
		this->_pointer = this->_base;
	}

	inline int size(void) const
	{
		return (int)(this->pointer - this->base);
	}
	
	inline int capacity(void) const
	{
		return this->memory;
	}

	void push(const T &x)
	{
		if(this->size() >= this->capacity())
			throw std::overflow_error("Stack overflow");
		*(this->_pointer++) = x;
	}
	
	T pop(void)
	{
		if(this->size() <= 0)
			throw std::underflow_error("Stack underflow");
		return *(--this->_pointer);
	}
	
	void pick(unsigned n)
	{
		if(this->size() <= n)
			throw std::underflow_error("Stack underflow");
		this->push(this->_pointer[-(int)(n+1)]);
	} 

	void roll(unsigned n)
	{
		this->pick(n);
		for(int i = -(int)(n+2); i <= -2; ++i)
		{
			this->pointer[i] = this->pointer[i+1];
		}
		this->drop();
	}
	
	T peek(void) const
	{
		const T x = this->pop();
		this->push(x);
		return x;
	}
	
	inline void dup(void)
	{
		this->pick(0);
	}
	
	inline void drop(void)
	{
		this->pop();
	}
	
	inline void swap(void)
	{
		this->roll(1);
	}
	
	inline void over(void)
	{
		this->pick(1);
	}
	
	inline void rot(void)
	{
		this->roll(2);
	}
	
	inline void nip(void) 
	{
		this->swap();
		this->drop();
	}
	
	inline void tuck(void)
	{
		this->swap();
		this->over();
	}
private:
	T  *_base;
	T  *_pointer;
	int _capacity;
};

#endif /* _STACK_HH_ */

