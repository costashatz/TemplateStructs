#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template<class T>
class TBinaryTreeNode
{
private:
	T value;
	TBinaryTreeNode<T>* left;
	TBinaryTreeNode<T>* right;
	TBinaryTreeNode<T>* parent;
public:
	TBinaryTreeNode()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
	}

	TBinaryTreeNode(const T& val)
	{
		value = val;
		left = NULL;
		right = NULL;
		parent = NULL;
	}

	void setLeft(TBinaryTreeNode<T>* l)
	{
		left = l;
	}

	void setRight(TBinaryTreeNode<T>* r)
	{
		right = r;
	}

	void setParent(TBinaryTreeNode<T>* p)
	{
		parent = p;
	}

	void setValue(const T& val)
	{
		value = val;
	}

	TBinaryTreeNode<T>* Left()
	{
		return left;
	}

	TBinaryTreeNode<T>* Right()
	{
		return right;
	}

	TBinaryTreeNode<T>* Parent()
	{
		return parent;
	}

	T& Value()
	{
		return value;
	}

	TBinaryTreeNode<T>& operator=(const TBinaryTreeNode<T>* other)
	{
		if(this == &other)
			return *this;
		delete right;
		delete left;
		delete parent;
		setValue(other->Value());
		setRight(other->Right());
		setLeft(other->Left());
		setParent(other->Parent());
		return *this;
	}
};

template<class T, class Array = TArray<T>>
class TBinaryTree
{
private:
typedef TBinaryTreeNode<T> node;
	node* head;
	int size;
	bool uniqueValues;
public:
	TBinaryTree()
	{
		size = 0;
		head = NULL;
		uniqueValues = false;
	}

	TBinaryTree(bool UniqueValues = false)
	{
		size = 0;
		head = NULL;
		uniqueValues = UniqueValues;
	}

	TBinaryTree(node* h, bool UniqueValues = false)
	{
		size = 1;
		head = h;
		uniqueValues = UniqueValues;
	}

	int Size()
	{
		return size;
	}

	bool Empty()
	{
		return (size==0);
	}

	bool UniqueValues()
	{
		return uniqueValues;
	}

	void setUnique(bool UniqueValues = true)
	{
		uniqueValues = UniqueValues;
	}

	void setHead(node* h)
	{
		if(head == NULL)
			head = h;
	}

	node* Head()
	{
		return head;
	}

	void addElement(const T& value)
	{
		node* x = new node(value);
		addElement(x);
	}

	void addElement(node* toAdd)
	{
		node* y = NULL;
		node* x = head;
		while(x != NULL)
		{
			y = x;
			if(toAdd->Value() < x->Value())
				x = x->Left();
			else if(toAdd->Value() > x->Value())
				x = x->Right();
			else
			{
				if(uniqueValues)
					return;
			}
		}
		toAdd->setParent(y);
		if(y == NULL)
		{
			head = toAdd;
		}
		else
		{
			if(toAdd->Value() < y->Value())
				y->setLeft(toAdd);
			else
				y->setRight(toAdd);
		}
		size++;
	}

	node* search(const T& val)
	{
		return searchNode(head, val);
	}

	node* searchNode(node* x, const T& val)
	{
		while(x != NULL && val != x->Value())
		{
			if(val < x->Value())
				x = x->Left();
			else
				x = x->Right();
		}
		return x;
	}

	node* minimum()
	{
		return minimumNode(head);
	}

	node* minimumNode(node* x)
	{
		if(x != NULL)
		{
			while(x->Left() != NULL)
				x = x->Left();
		}
		return x;
	}

	node* maximum()
	{
		return maximumNode(head);
	}

	node* maximumNode(node* x)
	{
		if(x != NULL)
		{
			while(x->Right() != NULL)
				x = x->Right();
		}
		return x;
	}

	node* successorOfNode(const T& value)
	{
		node* x = search(value);
		return successorOfNode(x);
	}

	node* successorOfNode(node* x)
	{
		node* y;
		if(x != NULL)
		{
			if(x->Right() != NULL)
				return minimumNode(x->Right());
			else
			{
				y = x->Parent();
				while(y != NULL && x == y->Right())
				{
					x = y;
					y = y->Parent();
				}
				return y;
			}
		}
		return NULL;
	}

	node* predecessorOfNode(const T& value)
	{
		node* x = search(value);
		return predecessorOfNode(x);
	}

	node* predecessorOfNode(node* x)
	{
		node* y;
		if(x != NULL)
		{
			if(x->Left() != NULL)
				return maximumNode(x->Left());
			else
			{
				y = x->Parent();
				while(y != NULL && x == y->Left())
				{
					x = y;
					y = y->Parent();
				}
				return y;
			}
		}
		return NULL;
	}

	node* remove(const T& val)
	{
		node* x = search(val);
		if(x == NULL)
			return x;
		return remove(x);
	}

	node* remove(node* x) //assuming that x is in tree && not null
	{
		node* y;
		node* z;
		if(x->Left() == NULL || x->Right() == NULL)
		{
			y = x;
		}
		else
		{
			y = successorOfNode(x);
		}
		if(y->Left() != NULL)
		{
			z = y->Left();
		}
		else
		{
			z = y->Right();
		}
		if(z != NULL)
		{
			z->setParent(y->Parent());
		}
		if(y->Parent() == NULL)
		{
			head = z;
		}
		else
		{
			if(y == y->Parent()->Left())
				y->Parent()->setLeft(z);
			else
				y->Parent()->setRight(z);
		}
		if(y != x)
		{
			x->setValue(y->Value());
		}
		size--;
		return y;
	}

	Array getInOrderArray()
	{
		Array arr = Array();
		getInOrderNode(head, arr);
		return arr;
	}

	void getInOrderNode(node* x, Array& arr)
	{
		if(x != NULL)
		{
			getInOrderNode(x->Left(), arr);
			arr.addBack(x->Value());
			getInOrderNode(x->Right(), arr);
		}
	}

	Array getPreOrderArray()
	{
		Array arr;
		getPreOrderNode(head, arr);
		return arr;
	}

	void getPreOrderNode(node* x, Array& arr)
	{
		if(x != NULL)
		{
			arr.addBack(x->Value());
			getPreOrderNode(x->Left(), arr);
			getPreOrderNode(x->Right(), arr);
		}
	}

	Array getPostOrderArray()
	{
		Array arr;
		getPostOrderNode(head, arr);
		return arr;
	}

	void getPostOrderNode(node* x, Array& arr)
	{
		if(x != NULL)
		{
			getPostOrderNode(x->Left(), arr);
			getPostOrderNode(x->Right(), arr);
			arr.addBack(x->Value());
		}
	}

	void displayPreOrder()
	{
		displayPreOrderNode(head);
	}

	void displayPreOrderNode(node* x)
	{
		if(x != NULL)
		{
			cout<<x->Value()<<endl;
			displayPreOrderNode(x->Left());
			displayPreOrderNode(x->Right());
		}
	}

	void displayInOrder()
	{
		displayInOrderNode(head);
	}

	void displayInOrderNode(node* x)
	{
		if(x != NULL)
		{
			displayInOrderNode(x->Left());
			std::cout<<x->Value()<<endl;
			displayInOrderNode(x->Right());
		}
	}

	void displayPostOrder()
	{
		displayPostOrderNode(head);
	}

	void displayPostOrderNode(node* x)
	{
		if(x != NULL)
		{
			displayPostOrderNode(x->Left());
			displayPostOrderNode(x->Right());
			std::cout<<x->Value()<<endl;
		}
	}

	void destroy()
	{
		destroyNode(head);
		size = 0;
		head = NULL;
	}

	void destroyNode(node* x)
	{
		if(x != NULL)
		{
			destroyNode(x->Left());
			destroyNode(x->Right());
			delete x;
			x = NULL;
		}
	}
};

#endif