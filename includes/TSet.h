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
#ifndef T_SET_H
#define T_SET_H
#include "TArray.h"


template<class T, class Tree = TRedBlackTree<T, TArray<T>>>
class TSet
{
private:
	Tree pSet;
public:
	TSet()
	{
		pSet = Tree(true);
	}

	int Size()
	{
		return pSet.Size();
	}

	bool Empty()
	{
		return pSet.Empty();
	}

	void Clear()
	{
		pSet.destroy();
		pSet.setHead(pSet.Nil());
	}

	void addElement(const T& value)
	{
		pSet.addElement(value);
	}

	Tree getTree()
	{
		return pSet;
	}

	T& remove(T value)
	{
		T x = T();
		x = pSet.remove(value)->Value();
		return x;
	}
};

#endif