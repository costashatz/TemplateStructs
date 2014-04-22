/*
    Copyright (C)  2013, 2014 Chatzilygeroudis Konstantinos


    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
    to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
    IN THE SOFTWARE.
*/
#ifndef T_STACK_H
#define T_STACK_H

template<class T, class Array = TArray<T> >
class TStack
{
private:
	Array pStack;
public:
	TStack()
	{
		pStack = Array();
	}

	Array getArray() { return pStack; }

	int Size()
	{
		return pStack.Size();
	}

	void Clear()
	{
		pStack.Clear();
	}

	void push(const T& value)
	{
		pStack.push_back(value);
	}

	T pop()
	{
		T x;
		x = pStack.remove(pStack.Size()-1);
		return x;
	}

	T& top()
	{
		return pStack[pStack.Size()-1];
	}

	bool Empty()
	{
		return pStack.Empty();
	}
};

#endif
