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
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
* TListElement Class
* Element of TList Class (double-linked list)
**/

template<class T>
class TListElement
{
private:
	T value;
	TListElement* previous;
	TListElement* next;
	TListElement* nil;
public:
	//constructors
	TListElement()
	{
		previous = NULL;
		next = NULL;
		nil = NULL;
	}

	TListElement(const T& val, TListElement<T>* NIL = NULL)
	{
		value = val;
		nil = NIL;
		previous = nil;
		next = nil;
	}

	TListElement(const T& val, TListElement<T>* prev, TListElement<T>* Next, TListElement<T>* NIL = NULL)
	{
		nil = NIL;
		value = val;
		previous = prev;
		next = Next;
	}

	void setValue(const T& val);
	void setNext(TListElement<T>* Next);
	void setPrev(TListElement<T>* prev);
	void setNil(TListElement<T>* NIL);
	T& Value();
	TListElement<T>* Prev();
	TListElement<T>* Next();
	TListElement<T>* Nil();

	TListElement<T>& operator=(const TListElement<T>* other)
	{
		if(this == &other)
			return *this;
		delete next;
		delete previous;
		setValue(other->Value());
		setNext(other->Next());
		setPrev(other->Prev());
		return *this;
	}

};

template<class T>
void TListElement<T>::setValue(const T& val)
{
	value = val;
}

template<class T>
void TListElement<T>::setNext(TListElement<T>* Next)
{
	if(Next != nil)
		next = Next;
	else
		next = nil;
}

template<class T>
void TListElement<T>::setPrev(TListElement<T>* prev)
{
	if(prev != nil)
		previous = prev;
	else
		previous = nil;
}

template<class T>
void TListElement<T>::setNil(TListElement<T>* NIL)
{
	if(previous == nil)
		previous = NIL;
	if(next == nil)
		next = NIL;
	nil = NIL;
}

template<class T>
T& TListElement<T>::Value()
{
	return value;
}

template<class T>
TListElement<T>* TListElement<T>::Prev()
{
	return previous;
}

template<class T>
TListElement<T>* TListElement<T>::Next()
{
	return next;
}

template<class T>
TListElement<T>* TListElement<T>::Nil()
{
	return nil;
}


/**
* TList Class
* Double-linked List
**/

template<class T>
class TList
{
private:
	TListElement<T>* nil;
	int size;
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
		typedef TListElement<T>* Node;

		iterator()
		{
			node = NULL;
		}

		iterator(Node n)
		{
			node = n;
		}

		iterator(iterator& a)
		{
			node = a.NODE();
		}

		Node NODE()
		{
			return node;
		}

		void setNode(Node n)
		{
			node = n;
		}


		self_type operator++()
		{
			node = node->Next();
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
			node = node->Prev();
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
			Node temp = node;
			int i=0;
			while(i<a)
			{
				if(temp->Prev() != temp->Nil())
				{
					temp = temp->Prev();
				}
				i++;
			}
			self_type b = self_type(temp);
			return b;
		}

		self_type operator-=(int a)
		{
			int i=0;
			while(i<a)
			{
				if(node->Prev() != node->Nil())
				{
					node = node->Prev();
				}
				i++;
			}
			return *this;
		}

		self_type operator+(int a)
		{
			Node temp = node;
			int i=0;
			while(i<a)
			{
				if(temp->Next() != node->Nil())
				{
					temp = temp->Next();
				}
				i++;
			}
			self_type b = self_type(temp);
			return b;
		}

		self_type operator+=(int a)
		{
			int i=0;
			while(i<a)
			{
				if(node->Next() != node->Nil())
				{
					node = node->Next();
				}
				i++;
			}
			return *this;
		}

		reference operator*()
		{
			return node->Value();
		}

		pointer operator->()
		{
			return &node->Value();
		}

		reference operator[](int i)
		{
			Node temp = node;
			int a=0;
			while(a<i)
			{
				if(temp->Next() != temp->Nil())
				{
					temp = temp->Next();
				}
				a++;
			}
			return temp->Value();
		}

		difference_type operator-(self_type& rhs)
		{
			difference_type i=0;
			Node temp = node->Nil()->Next();
			while(temp != node->Nil() && temp != node)
			{
				temp = temp->Next();
				i++;
			}
			temp = node->Nil()->Next();
			difference_type j=0;
			while(temp != node->Nil() && temp != rhs.NODE())
			{
				temp = temp->Next();
				j++;
			}
			difference_type a = i-j;
			return a;
		}

		self_type operator=(self_type& rhs)
		{
			node = rhs.NODE();
			return *this;
		}

		bool operator==(self_type& rhs)
		{
			return node == rhs.NODE();
		}

		bool operator!=(self_type& rhs)
		{
			return node != rhs.NODE();
		}

		bool operator>(self_type& rhs)
		{
			int i=0;
			Node temp = node->Nil()->Next();
			while(temp != node->Nil() && temp != node)
			{
				temp = temp->Next();
				i++;
			}
			temp = node->Nil()->Next();
			int j=0;
			while(temp != node->Nil() && temp != rhs.NODE())
			{
				temp = temp->Next();
				j++;
			}
			return i > j;
		}

		bool operator>=(self_type& rhs)
		{
			int i=0;
			Node temp = node->Nil()->Next();
			while(temp != node->Nil() && temp != node)
			{
				temp = temp->Next();
				i++;
			}
			temp = node->Nil()->Next();
			int j=0;
			while(temp != node->Nil() && temp != rhs.NODE())
			{
				temp = temp->Next();
				j++;
			}
			return i >= j;
		}

		bool operator<(self_type& rhs)
		{
			int i=0;
			Node temp = node->Nil()->Next();
			while(temp != node->Nil() && temp != node)
			{
				temp = temp->Next();
				i++;
			}
			temp = node->Nil()->Next();
			int j=0;
			while(temp != node->Nil() && temp != rhs.NODE())
			{
				temp = temp->Next();
				j++;
			}
			return i < j;
		}

		bool operator<=(self_type& rhs)
		{
			int i=0;
			Node temp = node->Nil()->Next();
			while(temp != node->Nil() && temp != node)
			{
				temp = temp->Next();
				i++;
			}
			temp = node->Nil()->Next();
			int j=0;
			while(temp != node->Nil() && temp != rhs.NODE())
			{
				temp = temp->Next();
				j++;
			}
			return i <= j;
		}

		private:
			Node node;
	};
	//constructors
	TList()
	{
		size = 0;
		nil = new TListElement<T>(0);
		nil->setNext(nil);
		nil->setPrev(nil);
		nil->setNil(nil);
	}

	TList(const T& fValue)
	{
		nil = new TListElement<T>(0);
		nil->setNext(nil);
		nil->setPrev(nil);
		nil->setNil(nil);
		nil->setNext(new TListElement<T>(fValue, nil, nil, nil));
		nil->setPrev(nil->Next());
		size = 1;
	}

	TList(TListElement<T>* f)
	{
		nil = new TListElement<T>(0);
		nil->setNext(nil);
		nil->setPrev(nil);
		nil->setNil(nil);
		nil->setNext(f);
		nil->setPrev(f);
		f->setNil(nil);
		f->setNext(nil);
		f->setPrev(nil);
		size = 1;
	}

	TListElement<T>* getRoot() { return nil->Next(); }
	TListElement<T>* getEnd() { return nil->Prev(); }
	int Size() { return size; }
	bool Empty() { return (size==0); }
	void Clear();
	void push_back(const T& value);
	void push_front(const T& value);
	void insert(const T& value, int index);
	void insert(const T& value, int index, int num);
	void insert(T* Array, int index, int iStart, int iEnd);

	iterator insert(const T& val, iterator position)
	{
		if(position >= end())
		{
			push_back(val);
			return end()-1;
		}
		else if(position <= begin())
		{
			push_front(val);
			return begin();
		}
		TListElement<T>* x = position.NODE();
		if(x != nil)
		{
			TListElement<T>* toAdd = new TListElement<T>(val, nil, nil, nil);
			x->Prev()->setNext(toAdd);
			toAdd->setPrev(x->Prev());
			toAdd->setNext(x);
			x->setPrev(toAdd);
			size++;
		}
		return position;
	}

	iterator insert(const T& val, iterator position, int num)
	{
		if(position >= end())
		{
			for(int i=0;i<num;i++)
				push_back(val);
			return end()-1;
		}
		else if(position <= begin())
		{
			for(int i=0;i<num;i++)
				push_front(val);
			return begin()+num-1;
		}
		for(int i=0;i<num;i++)
			insert(val, position);
		return position-1;
	}

	template<class Iter>
	iterator insert(iterator position, Iter iStart, Iter iEnd)
	{
		for(Iter it = iStart;it<iEnd;it++)
		{
			insert(*it, position);
		}
		return position-1;
	}

	iterator remove(iterator position)
	{
		TListElement<T>* x = position.NODE();
		if(x != nil)
		{
			x->Prev()->setNext(x->Next());
			x->Next()->setPrev(x->Prev());
			position.setNode(x->Next());
			size--;
			return position;
		}
		return iterator();
	}

	T& at(int index);
	TListElement<T>* getElement(int index);
	TListElement<T>* search(T key);
	TListElement<T>* remove(T key);
	TListElement<T>* removeIndex(int index);

	iterator begin()
	{
		return iterator(getRoot());
	}

	iterator end()
	{
		return iterator(nil);
	}

	T& operator [](int index)
	{
		return at(index);
	}
};

template<class T>
void TList<T>::Clear()
{
	TListElement<T>* x = nil->Next();
	TListElement<T>* temp;
	while(x != nil)
	{
		temp = x;
		x = x->Next();
		delete temp;
		temp = NULL;
	}
	size = 0;
}

template<class T>
void TList<T>::push_back(const T& value)
{
	TListElement<T>* toAdd = new TListElement<T>(value, nil);
	toAdd->setNext(nil);
	nil->Prev()->setNext(toAdd);
	toAdd->setPrev(nil->Prev());
	nil->setPrev(toAdd);
	size++;
}

template<class T>
void TList<T>::push_front(const T& value)
{
	TListElement<T>* toAdd = new TListElement<T>(value, nil);
	toAdd->setNext(nil->Next());
	nil->Next()->setPrev(toAdd);
	nil->setNext(toAdd);
	toAdd->setPrev(nil);
	size++;
}

template<class T>
void TList<T>::insert(const T& value, int index)
{
	if(index > Size())
		return push_back(value);
	else if(index < 0)
		return push_front(value);
	TListElement<T>* toAdd = new TListElement<T>(value, nil);
	TListElement<T>* x = getElement(index);
	if(x != nil)
	{
		x->Prev()->setNext(toAdd);
		toAdd->setPrev(x->Prev());
		toAdd->setNext(x);
		x->setPrev(toAdd);
		size++;
	}
}

template<class T>
void TList<T>::insert(const T& value, int index, int num)
{
	if(index >= Size())
	{
		index = Size();
	}
	else if(index <= 0)
	{
		index = 0;
	}
	for(int i=0;i<num;i++)
		insert(value, index);
}
	
template<class T>
void TList<T>::insert(T* Array, int index, int iStart, int iEnd)
{
	if(index > Size())
	{
		index = Size();
	}
	else if(index < 0)
	{
		index = 0;
	}
	if(iStart > iEnd)
	{
		int temp = iStart;
		iStart = iEnd;
		iEnd = temp;
	}
	int num = iEnd - iStart;
	for(int i=0;i<num;i++)
		insert(Array[iStart+i], index+i);
}

template<class T>
T& TList<T>::at(int index)
{
	TListElement<T>* x = getElement(index);
	if(x != nil)
	{
		return x->Value();
	}
	T* a = new T();
	return *a;
}

template<class T>
TListElement<T>* TList<T>::getElement(int index)
{
	if(index > Size())
		index = Size();
	else if(index < 0)
		index = 0;
	int i=0;
	TListElement<T>* x = nil->Next();
	while(x != nil)
	{
		if(i == index)
		{
			break;
		}
		x = x->Next();
		i++;
	}
	return x;
}

template<class T>
TListElement<T>* TList<T>::search(T key)
{
	TListElement<T>* x = nil->Next();
	while(x != nil && x->Value() != key)
	{
		x = x->Next();
	}
	return x;
}

template<class T>
TListElement<T>* TList<T>::remove(T key)
{
	TListElement<T>* x = search(key);
	if(x != nil)
	{
		x->Prev()->setNext(x->Next());
		x->Next()->setPrev(x->Prev());
		size--;
	}
	return x;
}

template<class T>
TListElement<T>* TList<T>::removeIndex(int index)
{
	if(index > Size())
		index = Size();
	else if(index < 0)
		index = 0;
	TListElement<T>* x = getElement(index);
	if(x != nil)
	{
		x->Prev()->setNext(x->Next());
		x->Next()->setPrev(x->Prev());
		size--;
	}
	return x;
}


#endif