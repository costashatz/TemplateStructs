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
#ifndef T_QUEUE_H
#define T_QUEUE_H

/**
* TQueue Class
* Queue
**/


template<class T, class Array = TArray<T> >
class TQueue
{
private:
	Array pQueue;
public:
	TQueue()
	{
		pQueue = Array();
	}

	Array getArray() { return pQueue; }

	int Size()
	{
		return pQueue.Size();
	}

	void Clear()
	{
		pQueue.Clear();
	}

	void push(const T& value)
	{
		pQueue.push_back(value);
	}

	T pop()
	{
		T x;
		x = pQueue.remove(0);
		return x;
	}

	T& front()
	{
		return pQueue[0];
	}

	bool Empty()
	{
		return pQueue.Empty();
	}
};

#endif
