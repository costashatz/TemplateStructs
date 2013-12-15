#ifndef T_ARRAY_H
#define T_ARRAY_H

//����� TArray: ��������� ������� �� ����������� ��������� �����

template<class T> //template ����� ��� ��� ���������� ������������ ����� ������
class TArray
{
private:
	T* pArray; //������� �� ��� ���� ��� ������
	int currSize; //������� ��� ��������������� ��� ��� ������
	int size; //���������� ������� ��� �����
	int maxSize; //������� ������� ��� ����� - 0=������
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

		iterator()
		{
			ptr = NULL;
		}

		iterator(iterator& a)
		{
			ptr = a.Ptr();
		}

		iterator(pointer a)
		{
			ptr = a;
		}

		pointer Ptr() { return ptr; }

		self_type operator++()
		{
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
			ptr--;
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
			self_type b = self_type(Ptr()-a);
			return b;
		}

		self_type operator-=(int a)
		{
			ptr -= a;
			return *this;
		}

		self_type operator+(int a)
		{
			self_type b = self_type(Ptr()+a);
			return b;
		}

		self_type operator+=(int a)
		{
			ptr += a;
			return *this;
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
			return ptr[i];
		}

		difference_type operator-(self_type& rhs)
		{
			difference_type a = ptr - rhs.Ptr();
			return a;
		}

		self_type operator=(self_type& rhs)
		{
			ptr = rhs.Ptr();
			return *this;
		}

		bool operator==(self_type& rhs)
		{
			return ptr == rhs.Ptr();
		}

		bool operator!=(self_type& rhs)
		{
			return ptr != rhs.Ptr();
		}

		bool operator>(self_type& rhs)
		{
			return ptr > rhs.Ptr();
		}

		bool operator>=(self_type& rhs)
		{
			return ptr >= rhs.Ptr();
		}

		bool operator<(self_type& rhs)
		{
			return ptr < rhs.Ptr();
		}

		bool operator<=(self_type& rhs)
		{
			return ptr <= rhs.Ptr();
		}

		private:
			pointer ptr;
	};
	//constructors
	TArray<T>()
	{
		size = 4;
		pArray = new T[4];
		currSize = 0;
		maxSize = 0;
	}
	TArray<T>(int initialNum, int MaxSize = 0)
	{
		if(MaxSize < 0)
			MaxSize = 0;
		if(initialNum < 0)
			initialNum = 4;
		maxSize = MaxSize;
		pArray = new T[3*initialNum/2];
		memset(pArray, T(), initialNum*sizeof(T));
		size = 3*initialNum/2;
		currSize = initialNum;
	}

	TArray<T>(T* Array, int num, int MaxSize = 0)
	{
		if(MaxSize < 0)
			MaxSize = 0;
		pArray = new T[3*num/2];
		memcpy(pArray, Array, num*sizeof(T));
		currSize = num;
		size = 3*num/2;
		maxSize = MaxSize;
		if(size > MaxSize)
			maxSize = size;
	}

	int Size(); //������� ��� ���������������
	int MemorySize(); //����������� ����� ��� �����
	int MaxSize(); //������� �������
	bool Empty(); //������ �������?
	bool resize(int newSize); //������ �������� ������
	T& at(int index); //��������� ��� ����� ��� ��������� ��� ���� index
	void push_back(const T& val); //�������� ����� ��� ����� ��� ������
	void push_front(const T& val); //�������� ����� ���� ���� ��� ������
	//void insert(int index, const T& val); //�������� ����� ��� ���� index ��� ������
	//void insert(int index, int num, const T& val = T()); //�������� ��������� ����� ��� ���� index
	void insert(T* Array, int index, int iStart, int iEnd); //�������� ����� ������ ��� ���� index
	T remove(int index); //�������� ��� ����� index
	T* remove(int iStart, int iEnd); //�������� �������� ��� ������
	iterator insert(iterator position, const T& val) //�������� ����� ��� ���� position
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
		int distFromBegin = position - begin();
		bool add = true;
		if((Size()+1) > MemorySize())
		{
			int x = (3*(MemorySize()+1)/2);
			if(x > MaxSize() && MaxSize() != 0 && (Size()+1) <= MaxSize())
				x = MaxSize();
			add = resize(x);
			position = begin() + distFromBegin;
		}
		if(add)
		{
			currSize++;
			memcpy(position.Ptr(), position.Ptr()-1, (end()-position)*sizeof(T));
			*position = val;
		}
		return position;
	}

	iterator insert(iterator position, int num, const T& val = T()) //�������� ��������� ����� ��� ���� position
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
		int distFromBegin = position - begin();
		bool add = true;
		if((Size()+num) > MemorySize())
		{
			int x = (3*(MemorySize() + num)/2);
			if(x > MaxSize() && MaxSize() != 0 && (Size()+num) <= MaxSize())
				x = MaxSize();
			add = resize(x);
			position = begin() + distFromBegin;
		}
		if(add)
		{
			currSize += num;
			memcpy(position.Ptr()+num, position.Ptr(), (end()-position)*sizeof(T));
			for(int i=0;i<num;i++)
				*(position++) = val;
		}
		return position-1;
	}

	template<class Iter>
	iterator insert(iterator position, Iter iStart, Iter iEnd)
	{
		for(Iter it = iStart;it!=iEnd;it++)
		{
			position = insert(*it, position);
			position++;
		}
		return position-1;
	}

	iterator remove(iterator position)
	{
		if(Size() > 0)
		{
			if(position > end())
			{
				position = end();
			}
			else if(position < begin())
			{
				position = begin();
			}
			memcpy(position.Ptr(), position.Ptr()+1, (end()-position)*sizeof(T));
			int x = (end()-position);
			currSize--;
			if(Size() < (MemorySize()/2))
				resize(3*Size()/2);
			position = end()-1-x;
			return position;
		}
		return iterator();
	}

	iterator remove(iterator iStart, iterator iEnd)
	{
		if(Size() > 0)
		{
			if(iStart > iEnd)
			{
				iterator temp = iStart;
				iStart = iEnd;
				iEnd = temp;
			}
			if(iEnd < begin())
				return new T();
			if(iStart > end())
				return new T();
			if(iStart < begin())
				iStart = begin();
			if(iEnd > end())
				iEnd = end();
			int num = iEnd - iStart;
			memcpy(iStart.Ptr(), iEnd.Ptr(), (Size()-num)*sizeof(T));
			currSize -= num;
			if(Size() < (MemorySize()/2))
				resize(3*Size()/2);
			return iStart;
		}
		return iterator();
	}
	void Clear(); //���������� ������
	void setMaxSize(int MaxSize); //������� �������� �������� - MaxSize < Size � MaxSize < MemorySize ���� MaxSize ��� �������
	T* getArray() { return pArray; }
	T& operator [](int index) //����������� ��� ������� [] ��� ��� ������ �������� ���� ����� ��� ������ (myArray[index])
	{
		return at(index);
	}

	iterator begin() { return iterator(pArray); }
	iterator end() { return iterator(pArray+Size()); }

	TArray<T>& operator =(const TArray* other) //����������� ��� ������� =
	{
		if(this == &other)
			return *this;
		if(other.Size() == 0)
			Clear();
		maxSize = other.MaxSize();
		resize(other.Size());
		memcpy( pArray, other.getArray(), other.Size() * sizeof(T) );
		currSize = other.Size();
		return *this;
	}
};

template<class T>
int TArray<T>::Size()
{
	return currSize;
}

template<class T>
int TArray<T>::MemorySize()
{
	return size;
}

template<class T>
int TArray<T>::MaxSize()
{
	return maxSize;
}

template<class T>
bool TArray<T>::Empty()
{
	return (currSize==0);
}

template<class T>
T& TArray<T>::at(int index)
{
	//������� ��� ��� ���������� ��� �� index �������� ��� ��� ������ (no error) -> ������ ������� ����� �� �������� �� ����� ������������ ���� ��� �������� ���� � �������
	if(index >= Size())
	{
		return pArray[Size()-1];
	}
	else if(index < 0)
	{
		return pArray[0];
	}
	return pArray[index];
}

template<class T>
bool TArray<T>::resize(int newSize)
{
	if(newSize <= 0) //�� ������� �� ������� �� ������� ��� ������ ��������� ��� 0 � �������� ��� �����������
		return false;
	if(maxSize != 0 && newSize > maxSize)
	{
		//Cannot go more than maxSize
		return false;
	}
	if(newSize < size)
		size = newSize;
	T* newArr = new T[newSize];
	memcpy( newArr, pArray, size * sizeof(T) );
	delete [] pArray;
	pArray = newArr;
	size = newSize;
	return true;
}

template<class T>
void TArray<T>::push_back(const T& val)
{
	bool add = true;
	if((Size()+1) > MemorySize())
	{
		int x = (3*(MemorySize()+1)/2);
		if(x > MaxSize() && MaxSize() != 0 && (Size()+1) <= MaxSize())
			x = MaxSize();
		add = resize(x);
	}
	if(add)
	{
		currSize++;
		pArray[Size()-1] = val;
	}
}

template<class T>
void TArray<T>::push_front(const T& val)
{
	bool add = true;
	if((Size()+1) > MemorySize())
	{
		int x = (3*(MemorySize()+1)/2);
		if(x > MaxSize() && MaxSize() != 0 && (Size()+1) <= MaxSize())
			x = MaxSize();
		add = resize(x);
	}
	if(add)
	{
		currSize++;
		memcpy(pArray+1, pArray, (Size()-1)*sizeof(T));
		pArray[0] = val;
	}
}

/*template<class T>
void TArray<T>::insert(int index, const T& val)
{
	if(index >= Size())
	{
		push_back(val);
		return;
	}
	else if(index <= 0)
	{
		push_front(val);
		return;
	}
	bool add = true;
	if((Size()+1) > MemorySize())
	{
		int x = (3*(MemorySize()+1)/2);
		if(x > MaxSize() && MaxSize() != 0 && (Size()+1) <= MaxSize())
			x = MaxSize();
		add = resize(x);
	}
	if(add)
	{
		currSize++;
		memcpy(pArray+index, pArray+index-1, (Size()-index)*sizeof(T));
		pArray[index] = val;
	}
}


template<class T>
void TArray<T>::insert(int index, int num, const T& val = T())
{
	if(index > Size())
	{
		index = Size();
	}
	else if(index < 0)
	{
		index = 0;
	}
	bool add = true;
	if((Size()+num) > MemorySize())
	{
		int x = (3*(MemorySize() + num)/2);
		if(x > MaxSize() && MaxSize() != 0 && (Size()+num) <= MaxSize())
			x = MaxSize();
		add = resize(x);
	}
	if(add)
	{
		memcpy(pArray+index+num, pArray+index, (Size()-index)*sizeof(T));
		currSize += num;
		for(int i=index;i<(index+num);i++)
			pArray[i] = val;
	}
}*/

template<class T>
void TArray<T>::insert(T* Array, int index, int iStart, int iEnd)
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
	bool add = true;
	if((Size()+num) > MemorySize())
	{
		int x = (3*(MemorySize() + num)/2);
		if(x > MaxSize() && MaxSize() != 0 && (Size()+num) <= MaxSize())
			x = MaxSize();
		add = resize(x);
	}
	if(add)
	{
		memcpy(pArray+index+num, pArray+index, (Size()-index)*sizeof(T));
		currSize += num;
		memcpy(pArray+index, Array+iStart, num*sizeof(T));
	}
}

template<class T>
T TArray<T>::remove(int index)
{
	if(Size() > 0)
	{
		if(index >= Size())
		{
			return remove(Size()-1);
		}
		else if(index < 0)
		{
			return remove(0);
		}
		
		T x = pArray[index];
		memcpy(pArray+index, pArray+index+1, (Size()-index)*sizeof(T));
		currSize--;
		if(Size() < (MemorySize()/2))
			resize(3*Size()/2);
		return x;
	}
	return T();
}

template<class T>
T* TArray<T>::remove(int iStart, int iEnd)
{
	if(Size() > 0)
	{
		if(iStart > iEnd)
		{
			int temp = iStart;
			iStart = iEnd;
			iEnd = temp;
		}
		if(iEnd < 0)
			return new T();
		if(iStart > Size())
			return new T();
		if(iStart < 0)
			iStart = 0;
		if(iEnd > Size())
			iEnd = Size();
		int num = iEnd - iStart;
		T* x = new T[num];
		memcpy(x, pArray+iStart, num*sizeof(T));
		memcpy(pArray+iStart, pArray+iEnd, (Size()-num)*sizeof(T));
		currSize -= num;
		if(Size() < (MemorySize()/2))
			resize(3*Size()/2);
		return x;
	}
	return new T();
}

template<class T>
void TArray<T>::Clear()
{
	currSize = 0;
	delete [] pArray;
	pArray = new T[4];
	size = 4;
}

template<class T>
void TArray<T>::setMaxSize(int MaxSize)
{
	if(MaxSize == 0)
	{
		maxSize = 0;
		return;
	}
	if((MaxSize < Size()) || (MaxSize < MemorySize()))
		return;
	maxSize = MaxSize;
}


#endif