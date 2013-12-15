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