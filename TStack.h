#ifndef T_STACK_H
#define T_STACK_H

//κλάση TStack: απλή υλοποίηση στοίβας με δυνατότητα αλλαγής του μέσου αποθήκευσης (πρέπει να υποστηρίζει push_back(), Size(), remove(), Empty(), [])

template<class T, class Array = TArray<T>>
class TStack
{
private:
	Array pStack; //πίνακας αποθήκευσης
public:
	TStack()
	{
		pStack = Array();
	}

	Array getArray() { return pStack; } //επιστροφή πίνακα

	int Size() //μέγεθος
	{
		return pStack.Size();
	}

	void Clear()
	{
		pStack.Clear();
	}

	void push(const T& value) //προσθήκη τιμής στη στοίβα
	{
		pStack.push_back(value);
	}

	T pop() //εξαγωγή πάνω τιμής
	{
		T x;
		x = pStack.remove(pStack.Size()-1);
		return x;
	}

	T& top() //επιστροφή πάνω τιμής
	{
		return pStack[pStack.Size()-1];
	}

	bool Empty() //άδειος?
	{
		return pStack.Empty();
	}
};

#endif