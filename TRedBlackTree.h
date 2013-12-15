#ifndef T_RED_BLACK_TREE_H
#define T_RED_BLACK_TREE_H


enum COLOR
	{ RED, BLACK};

template<class T>
class TBinaryBlackTreeNode
{
private:
	typedef TBinaryBlackTreeNode<T> Node;
	T value;
	Node* left;
	Node* right;
	Node* parent;
	COLOR color;
public:
	TBinaryBlackTreeNode()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		color = BLACK;
	}

	TBinaryBlackTreeNode(const T& val, const COLOR& col)
	{
		value = val;
		left = NULL;
		right = NULL;
		parent = NULL;
		color = col;
	}

	void setLeft(Node* l)
	{
		left = l;
	}

	void setRight(Node* r)
	{
		right = r;
	}

	void setParent(Node* p)
	{
		parent = p;
	}

	void setValue(const T& val)
	{
		value = val;
	}

	void setColor(const COLOR& col)
	{
		color = col;
	}

	Node* Left()
	{
		return left;
	}

	Node* Right()
	{
		return right;
	}

	Node* Parent()
	{
		return parent;
	}

	Node* GrandParent()
	{
		if(Parent() != NULL)
		{
			return Parent()->Parent();
		}
		return NULL;
	}

	Node* Uncle()
	{
		Node* g = GrandParent();
		if(g == NULL)
			return NULL;
		if(Parent() == g->Left())
			return g->Right();
		else
			return g->Left();
	}

	T& Value()
	{
		return value;
	}

	COLOR& Color()
	{
		return color;
	}

	Node& operator=(const Node* other)
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
		setColor(other->Color());
		return *this;
	}
};


template<class T, class Array = TArray<T>>
class TRedBlackTree
{
private:
	typedef TBinaryBlackTreeNode<T> Node;
	Node* head;
	int size;
	Node* nil;
	bool uniqueValues;
public:
	TRedBlackTree()
	{
		nil = new Node();
		nil->setColor(BLACK);
		head = nil;
		size = 0;
		uniqueValues = false;
	}

	TRedBlackTree(bool UniqueValues)
	{
		nil = new Node();
		nil->setColor(BLACK);
		head = nil;
		size = 0;
		uniqueValues = UniqueValues;
	}

	TRedBlackTree(Node* h, bool UniqueValues = false)
	{
		head = h;
		head->setColor(BLACK);
		nil = new Node();
		nil->setParent(nil);
		nil->setColor(BLACK);
		head->setParent(nil);
		size = 1;
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

	void setHead(Node* h)
	{
		if(head == NULL)
		{
			head = h;
			head->setColor(BLACK);
		}
	}

	Node* Head()
	{
		return head;
	}

	Node* Nil()
	{
		return nil;
	}

	void LeftRotate(Node* x)
	{
		Node* y = x->Right();
		if(y != nil)
		{
			x->setRight(y->Left());
			if(y->Left() != nil)
				y->Left()->setParent(x);
			y->setParent(x->Parent());
			if(x->Parent() == nil)
				head = y;
			else if(x == x->Parent()->Left())
				x->Parent()->setLeft(y);
			else
				x->Parent()->setRight(y);
			y->setLeft(x);
			x->setParent(y);
		}
	}

	void RightRotate(Node* x)
	{
		Node* y = x->Left();
		if(y != nil)
		{
			x->setLeft(y->Right());
			if(y->Right() != nil)
				y->Right()->setParent(x);
			y->setParent(x->Parent());
			if(x->Parent() == nil)
				head = y;
			else if(x == x->Parent()->Left())
				x->Parent()->setLeft(y);
			else
				x->Parent()->setRight(y);
			y->setRight(x);
			x->setParent(y);
		}
	}

	Node* search(const T& val)
	{
		return searchNode(head, val);
	}

	Node* searchNode(Node* x, const T& val)
	{
		while(x != nil && val != x->Value())
		{
			if(val < x->Value())
				x = x->Left();
			else
				x = x->Right();
		}
		return x;
	}

	Node* minimum()
	{
		return minimumNode(head);
	}

	Node* minimumNode(Node* x)
	{
		if(x != nil)
		{
			while(x->Left() != nil)
				x = x->Left();
		}
		return x;
	}

	Node* maximum()
	{
		return maximumNode(head);
	}

	Node* maximumNode(Node* x)
	{
		if(x != nil)
		{
			while(x->Right() != nil)
				x = x->Right();
		}
		return x;
	}

	Node* successorOfNode(const T& value)
	{
		Node* x = search(value);
		return successorOfNode(x);
	}

	Node* successorOfNode(Node* x)
	{
		Node* y;
		if(x != nil)
		{
			if(x->Right() != nil)
				return minimumNode(x->Right());
			else
			{
				y = x->Parent();
				while(y != nil && x == y->Right())
				{
					x = y;
					y = y->Parent();
				}
				return y;
			}
		}
		return nil;
	}

	Node* predecessorOfNode(const T& value)
	{
		Node* x = search(value);
		return predecessorOfNode(x);
	}

	Node* predecessorOfNode(Node* x)
	{
		Node* y;
		if(x != nil)
		{
			if(x->Left() != nil)
				return maximumNode(x->Left());
			else
			{
				y = x->Parent();
				while(y != nil && x == y->Left())
				{
					x = y;
					y = y->Parent();
				}
				return y;
			}
		}
		return nil;
	}

	void addElement(const T& value)
	{
		Node* x = new Node(value, RED);
		addElement(x);
	}

	void addElement(Node* toAdd)
	{
		Node* y = nil;
		Node* x = head;
		while(x != nil)
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
		if(y == nil)
		{
			head = toAdd;
			head->setLeft(nil);
			head->setRight(nil);
			head->setColor(BLACK);
			head->setParent(nil);
			size++;
		}
		else
		{
			if(toAdd->Value() < y->Value())
				y->setLeft(toAdd);
			else
				y->setRight(toAdd);
			toAdd->setLeft(nil);
			toAdd->setRight(nil);
			toAdd->setColor(RED);
			size++;
		}
		insertFixUp(toAdd);
	}

	void insertFixUp(Node* z)
	{
		Node* y = nil;
		while(z->Parent()->Color() == RED)
		{
			if(z->Parent() == z->Parent()->Parent()->Left())
			{
				y = z->Parent()->Parent()->Right();
				if(y->Color() == RED)
				{
					z->Parent()->setColor(BLACK);
					y->setColor(BLACK);
					z->Parent()->Parent()->setColor(RED);
					z = z->Parent()->Parent();
				}
				else 
				{
					if(z == z->Parent()->Right())
					{
						z = z->Parent();
						LeftRotate(z);
					}
					z->Parent()->setColor(BLACK);
					z->Parent()->Parent()->setColor(RED);
					RightRotate(z->Parent()->Parent());
				}
			}
			else
			{
				y = z->Parent()->Parent()->Left();
				if(y->Color() == RED)
				{
					z->Parent()->setColor(BLACK);
					y->setColor(BLACK);
					z->Parent()->Parent()->setColor(RED);
					z = z->Parent()->Parent();
				}
				else 
				{
					if(z == z->Parent()->Left())
					{
						z = z->Parent();
						RightRotate(z);
					}
					z->Parent()->setColor(BLACK);
					z->Parent()->Parent()->setColor(RED);
					LeftRotate(z->Parent()->Parent());
				}
			}
		}
		head->setColor(BLACK);
	}

	Node* remove(const T& value)
	{
		Node* x = search(value);
		if(x == nil)
			return x;
		return remove(x);
	}

	Node* remove(Node* z)
	{
		Node* y;
		Node* x;
		if(z->Left() == nil || z->Right() == nil)
		{
			y = z;
		}
		else
		{
			y = successorOfNode(z);
		}
		if(y->Left() != nil)
		{
			x = y->Left();
		}
		else
		{
			x = y->Right();
		}
		x->setParent(y->Parent());
		if(y->Parent() == nil)
		{
			head = x;
		}
		else
		{
			if(y == y->Parent()->Left())
			{
				y->Parent()->setLeft(x);
			}
			else
			{
				y->Parent()->setRight(x);
			}
		}
		if(y != z)
			z->setValue(y->Value());
		if(y->Color() == BLACK)
			removeFixUp(x);
		return y;
	}

	void removeFixUp(Node* x)
	{
		Node* w = nil;
		while(x != head && x->Color() == BLACK)
		{
			if(x == x->Parent()->Left())
			{
				w = x->Parent()->Right();
				if(w->Color() == RED)
				{
					w->setColor(BLACK);
					x->Parent()->setColor(RED);
					LeftRotate(x->Parent());
					w = x->Parent()->Right();
				}
				if(w->Left()->Color() == BLACK && w->Right()->Color() == BLACK)
				{
					w->setColor(RED);
					x = x->Parent();
				}
				else
				{
					if(w->Right()->Color() == BLACK)
					{
						w->Left()->setColor(BLACK);
						w->setColor(RED);
						RightRotate(w);
						w = x->Parent()->Right();
					}
					w->setColor(x->Parent()->Color());
					x->Parent()->setColor(BLACK);
					w->Right()->setColor(BLACK);
					LeftRotate(x->Parent());
					x = head;
				}
			}
			else
			{
				w = x->Parent()->Left();
				if(w->Color() == RED)
				{
					w->setColor(BLACK);
					x->Parent()->setColor(RED);
					RightRotate(x->Parent());
					w = x->Parent()->Left();
				}
				if(w->Left()->Color() == BLACK && w->Right()->Color() == BLACK)
				{
					w->setColor(RED);
					x = x->Parent();
				}
				else
				{
					if(w->Left()->Color() == BLACK)
					{
						w->Right()->setColor(BLACK);
						w->setColor(RED);
						LeftRotate(w);
						w = x->Parent()->Left();
					}
					w->setColor(x->Parent()->Color());
					x->Parent()->setColor(BLACK);
					w->Left()->setColor(BLACK);
					RightRotate(x->Parent());
					x = head;
				}
			}
		}
	}

	Array getInOrderArray()
	{
		Array arr = Array();
		getInOrderNode(head, arr);
		return arr;
	}

	void getInOrderNode(Node* x, Array& arr)
	{
		if(x != nil)
		{
			getInOrderNode(x->Left(), arr);
			arr.addBack(x->Value());
			getInOrderNode(x->Right(), arr);
		}
	}

	void displayInOrder()
	{
		displayInOrderNode(head);
	}

	void displayInOrderNode(Node* x)
	{
		if(x != nil)
		{
			displayInOrderNode(x->Left());
			std::cout<<x->Value()<<": "<<x->Color()<<endl;
			displayInOrderNode(x->Right());
		}
	}

	void displayPreOrder()
	{
		displayPreOrderNode(head);
	}

	void displayPreOrderNode(Node* x)
	{
		if(x != nil)
		{
			std::cout<<x->Value()<<", "<<x->Color()<<endl;
			displayPreOrderNode(x->Left());
			displayPreOrderNode(x->Right());
		}
	}

	void destroy()
	{
		destroyNode(head);
		size = 0;
		head = nil;
	}

	void destroyNode(Node* x)
	{
		if(x != NULL && x != nil)
		{
			destroyNode(x->Left());
			destroyNode(x->Right());
			delete x;
			x = NULL;
		}
	}
};


#endif