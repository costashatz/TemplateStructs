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
#ifndef T_DEQUE_H
#define T_DEQUE_H


template<class T, class Array = TArray<T> >
class TDeque
{
private:
	Array pDequeFront;
	Array pDequeBack;
	int maxSize;
public:

	class iterator
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef iterator self_type;
		typedef std::random_access_iterator_tag iterator_category;
		typedef int difference_type;
		typedef TDeque<T> cont;

		iterator()
		{
			ptr = NULL;
		}

		iterator(const iterator& a)
		{
			ptr = a.ptr;
			deq = a.Deque();
		}

		iterator(pointer a, cont Deq)
		{
			ptr = a;
			deq = Deq;
		}

		pointer Ptr() { return ptr; }

		cont Deque() const { return deq; }

		cont Deque() { return deq; }

		bool isInRange(pointer p, pointer s, pointer e)
		{
			if(p >= s && p <= e)
				return true;
			return false;
		}

		self_type operator++()
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()))
			{
				ptr--;
				if(!isInRange(ptr, fStart.Ptr(), fEnd.Ptr()))
				{
					ptr = bStart.Ptr();
				}
			}
			else
				ptr++;
			return *this;
		}

		self_type operator++(int junk)
		{
			self_type i = *this;
			++*this;
			return i;
		}

		self_type operator--()
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()))
				ptr++;
			else
			{
				ptr--;
				if(!isInRange(ptr, bStart.Ptr(), bEnd.Ptr()))
					ptr = fStart.Ptr();
			}
			return *this;
		}

		self_type operator--(int junk)
		{
			self_type i = *this;
			--*this;
			return i;
		}

		self_type operator-(int a)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()))
			{
				self_type b = self_type(Ptr()+a, deq);
				return b;
			}
			else if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()))
			{
				difference_type x = ptr - bStart.Ptr();
				if(x >= a)
				{
					self_type b = self_type(Ptr()-a, deq);
					return b;
				}
				else
				{
					difference_type k = a - x;
					self_type b = self_type(fStart.Ptr()+k, deq);
					return b;
				}
			}
			self_type b2 = self_type(Ptr()-a, deq);
			return b2;
		}

		self_type operator-=(int a)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()))
			{
				ptr += a;
				return *this;
			}
			else if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()))
			{
				difference_type x = ptr - bStart.Ptr();
				if(x >= a)
				{
					ptr -= a;
					return *this;
				}
				else
				{
					difference_type k = a - x;
					ptr = fStart.Ptr()+k;
					return *this;
				}
			}
			return *this;
		}

		self_type operator+(int a)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()))
			{
				difference_type x = ptr - fStart.Ptr();
				if(x >= a)
				{
					self_type b = self_type(Ptr()-a, deq);
					return b;
				}
				else
				{
					difference_type k = a - x;
					self_type b = self_type(bStart.Ptr()+k, deq);
					return b;
				}
			}
			else
			{
				self_type b = self_type(Ptr()+a, deq);
				return b;
			}
		}

		self_type operator+=(int a)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()))
			{
				difference_type x = ptr - fStart.Ptr();
				if(x >= a)
				{
					ptr -= a;
					return *this;
				}
				else
				{
					difference_type k = a - x;
					ptr = bStart.Ptr()+k;
					return *this;
				}
			}
			else
			{
				ptr += a;
				return *this;
			}
		}

		reference operator*()
		{
			return *ptr;
		}

		pointer operator->()
		{
			return ptr;
		}

		reference operator[](int i)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()))
			{
				difference_type x = ptr - fStart.Ptr();
				if(x >= i)
				{
					return ptr[f.Size()-1-i];
				}
				else
				{
					difference_type k = i - x;
					return bStart[k];
				}
			}
			return ptr[i];
		}

		difference_type operator-(const self_type& rhs)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()) && isInRange(rhs.ptr, fStart.Ptr(), fEnd.Ptr()))
				return (ptr - rhs.ptr);
			else if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()) && isInRange(rhs.ptr, bStart.Ptr(), bEnd.Ptr()))
				return (ptr - rhs.ptr);
			else
			{
				if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()))
				{
					difference_type x = ptr - bStart.Ptr();
					difference_type a = rhs.ptr - fStart.Ptr();
					return a+x+1;
				}
				else
				{
					difference_type x = ptr - fStart.Ptr();
					difference_type a = rhs.ptr - bStart.Ptr();
					return a+x+1;
				}
			}
			difference_type a = ptr - rhs.ptr;
			return a;
		}

		self_type operator=(const self_type& rhs)
		{
			ptr = rhs.ptr;
			deq = rhs.Deque();
			return *this;
		}

		bool operator==(const self_type& rhs)
		{
			return ptr == rhs.ptr;
		}

		bool operator!=(const self_type& rhs)
		{
			return ptr != rhs.ptr;
		}

		bool operator>(const self_type& rhs)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()) && isInRange(rhs.ptr, fStart.Ptr(), fEnd.Ptr()))
				return (ptr < rhs.ptr);
			else if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()) && isInRange(rhs.ptr, bStart.Ptr(), bEnd.Ptr()))
				return (ptr > rhs.ptr);
			else
			{
				if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return ptr > rhs.ptr;
		}

		bool operator>=(const self_type& rhs)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()) && isInRange(rhs.ptr, fStart.Ptr(), fEnd.Ptr()))
				return (ptr <= rhs.ptr);
			else if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()) && isInRange(rhs.ptr, bStart.Ptr(), bEnd.Ptr()))
				return (ptr >= rhs.ptr);
			else
			{
				if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			return ptr >= rhs.ptr;
		}

		bool operator<(const self_type& rhs)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()) && isInRange(rhs.ptr, fStart.Ptr(), fEnd.Ptr()))
				return (ptr > rhs.ptr);
			else if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()) && isInRange(rhs.ptr, bStart.Ptr(), bEnd.Ptr()))
				return (ptr < rhs.ptr);
			else
			{
				if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()))
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			return ptr < rhs.ptr;
		}

		bool operator<=(const self_type& rhs)
		{
			Array f = deq.getFrontArray();
			typename Array::iterator fStart = f.begin();
			typename Array::iterator fEnd = f.end();
			Array b = deq.getBackArray();
			typename Array::iterator bStart = b.begin();
			typename Array::iterator bEnd = b.end();
			if(isInRange(ptr, fStart.Ptr(), fEnd.Ptr()) && isInRange(rhs.ptr, fStart.Ptr(), fEnd().Ptr()))
				return (ptr >= rhs.ptr);
			else if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()) && isInRange(rhs.ptr, bStart.Ptr(), bEnd().Ptr()))
				return (ptr <= rhs.ptr);
			else
			{
				if(isInRange(ptr, bStart.Ptr(), bEnd.Ptr()))
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			return ptr <= rhs.ptr;
		}

		private:
			pointer ptr;
			cont deq;
	};
	//constructors
	TDeque()
	{
		pDequeFront = Array();
		pDequeBack = Array();
		maxSize = 0;
	}

	TDeque(int initialNum, int MaxSize=0)
	{
		pDequeFront = Array(initialNum/2);
		pDequeBack = Array(initialNum - (initialNum/2));
		setMaxSize(MaxSize);
	}

	TDeque(T* Arr, int num, int MaxSize = 0)
	{
		pDequeFront = Array();
		pDequeBack = Array(Arr, num);
		if(MaxSize != 0)
			setMaxSize(MaxSize);
	}

	TDeque<T>& operator =(const TDeque* other)
	{
		if(this == &other)
			return *this;
		pDequeFront = other->getFrontArray();
		pDequeBack = other->getBackArray();
		maxSize = other->MaxSize();
		return *this;
	}

	void setMaxSize(int MaxSize)
	{
		maxSize = MaxSize;
		if(maxSize < (pDequeBack.Size() + pDequeFront.Size()))
			maxSize = pDequeBack.Size() + pDequeFront.Size();
		pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
		pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
	}

	Array getFrontArray()
	{
		return pDequeFront;
	}

	Array getBackArray()
	{
		return pDequeBack;
	}

	Array getArray()
	{
		Array x = Array(Size());
		for(int i=0;i<pDequeFront.Size();i++)
			x.push_back(pDequeFront[pDequeFront.Size()-1-i]);
		for(int i=0;i<pDequeBack.Size();i++)
			x.push_back(pDequeBack[i]);
		return x;
	}

	iterator begin()
	{
		iterator i = iterator(pDequeFront.end().Ptr(), *this);
		i++;
		return i;
	}

	iterator end()
	{
		return iterator(pDequeBack.end().Ptr(), *this);
	}

	int Size()
	{
		return (pDequeBack.Size() + pDequeFront.Size());
	}

	int MaxSize()
	{
		return maxSize;
	}

	bool Empty()
	{
		return (Size()==0);
	}

	void Clear()
	{
		pDequeFront.Clear();
		pDequeBack.Clear();
	}

	void push_back(const T& value)
	{
		pDequeBack.push_back(value);
		if(maxSize != 0)
			pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
	}

	void push_front(const T& value)
	{
		pDequeFront.push_back(value);
		if(maxSize != 0)
			pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
	}

	T& at(int index)
	{
		if(index > Size())
			index = Size();
		else if(index < 0)
			index = 0;
		if(index >= pDequeFront.Size())
			return pDequeBack.at(index-pDequeFront.Size());
		else
			return pDequeFront.at(pDequeFront.Size()-index-1);
	}

	T& operator [](int index)
	{
		return at(index);
	}

	void insert(const T& value, int index)
	{
		if(index <= 0)
			return push_front(value);
		else if(index >= Size())
			return push_back(value);
		if(index >= pDequeFront.Size())
		{
			pDequeBack.insert(value, index-pDequeFront.Size());
			if(maxSize != 0)
				pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
			return;
		}
		else
		{
			pDequeFront.insert(value, pDequeFront.Size()-index);
			if(maxSize != 0)
				pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
			return;
		}
	}

	void insert(const T& value, int index, int num)
	{
		if(index <= 0)
		{
			pDequeFront.insert(value, pDequeFront.Size(), num);
			if(maxSize != 0)
				pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
			return;
		}
		else if(index >= Size())
		{
			pDequeBack.insert(value, pDequeBack.Size(), num);
			if(maxSize != 0)
				pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
			return;
		}
		if(index >= pDequeFront.Size())
		{
			pDequeBack.insert(value, index-pDequeFront.Size(), num);
			if(maxSize != 0)
				pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
		}
		else
		{
			pDequeFront.insert(value, pDequeFront.Size()-index, num);
			if(maxSize != 0)
				pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
		}
	}

	void insert(T* Arr, int index, int iStart, int iEnd)
	{
		if(index <= 0)
		{
			pDequeFront.insert(Arr, index, iStart, iEnd);
			if(maxSize != 0)
				pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
			return;
		}
		else if(index >= Size())
		{
			pDequeBack.insert(Arr, index, iStart, iEnd);
			if(maxSize != 0)
				pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
			return;
		}
		if(index >= pDequeFront.Size())
		{
			pDequeBack.insert(Arr, index-pDequeFront.Size(), iStart, iEnd);
			if(maxSize != 0)
				pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
		}
		else
		{
			if(iStart > iEnd)
			{
				int temp = iStart;
				iStart = iEnd;
				iEnd = temp;
			}
			int num = iEnd - iStart;
			T* arr = new T[num];
			memcpy(arr, Arr+iStart, num*sizeof(T));
			for(int i=0;i<num/2;i++)
			{
				T temp = arr[i];
				arr[i] = arr[num-i-1];
				arr[num-i-1] = temp;
			}
			pDequeFront.insert(arr, pDequeFront.Size()-index, 0, num);
			if(maxSize != 0)
				pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
		}
	}
	
	T pop_front()
	{
		T x = pDequeFront.remove(pDequeFront.Size()-1);
		pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
		return x;
	}

	T pop_back()
	{
		T x = pDequeBack.remove(pDequeBack.Size()-1);
		pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
		return x;
	}

	T remove(int index)
	{
		if(index <= 0)
		{
			return pop_front();
		}
		else if(index >= Size())
		{
			return pop_back();
		}
		if(index >= pDequeFront.Size())
		{
			pDequeBack.remove(index-pDequeFront.Size());
			if(maxSize != 0)
				pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
		}
		else
		{
			pDequeFront.remove(pDequeFront.Size()-index);
			if(maxSize != 0)
				pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
		}
	}

	T* remove(int iStart, int iEnd)
	{
		if(iStart > iEnd)
		{
			int temp = iStart;
			iStart = iEnd;
			iEnd = temp;
		}
		int num = iEnd - iStart;
		int backNum = iEnd - ((iStart<pDequeFront.Size())?pDequeFront.Size():iStart);
		int frontNum = num - ((backNum>0)?backNum:0);
		T* x = new T[num];
		if(frontNum > 0)
		{
			T* y = pDequeFront.remove(pDequeFront.Size()-iStart, pDequeFront.Size()-iStart - frontNum);
			memcpy(x, y, frontNum*sizeof(T));
		}
		if(backNum > 0)
		{
			int index = iStart - pDequeFront.Size();
			index = (index > 0) ? index : 0;
			T* y = pDequeBack.remove(index, index+backNum);
			memcpy(x+((frontNum>0)?frontNum:0), y, backNum*sizeof(T));
		}
		pDequeBack.setMaxSize(maxSize - pDequeFront.Size());
		pDequeFront.setMaxSize(maxSize - pDequeBack.Size());
		return x;
	}
};

#endif