#ifndef T_QUEUE_H
#define T_QUEUE_H

//κλάση TQueue: απλή υλοποίηση ουράς με δυνατότητα αλλαγής του μέσου αποθήκευσης (πρέπει να υποστηρίζει push_back(), Size(), remove(), Empty(), Clear(), [])

template<class T, class Array = TArray<T>>
class TQueue
{
private:
	Array pQueue; //πίνακας αποθήκευσης
public:
	TQueue()
	{
		pQueue = Array();
	}

	Array getArray() { return pQueue; } //επιστροφή πίνακα

	int Size() //μέγεθος
	{
		return pQueue.Size();
	}

	void Clear()
	{
		pQueue.Clear();
	}

	void push(const T& value) //προσθήκη τιμής στην ουρά
	{
		pQueue.push_back(value);
	}

	T pop() //εξαγωγή πάνω τιμής
	{
		T x;
		x = pQueue.remove(0);
		return x;
	}

	T& front() //επιστροφή πάνω τιμής
	{
		return pQueue[0];
	}

	bool Empty() //άδειος?
	{
		return pQueue.Empty();
	}
};

#endif