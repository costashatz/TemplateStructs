#ifndef T_QUEUE_H
#define T_QUEUE_H

//����� TQueue: ���� ��������� ����� �� ���������� ������� ��� ����� ����������� (������ �� ����������� push_back(), Size(), remove(), Empty(), Clear(), [])

template<class T, class Array = TArray<T>>
class TQueue
{
private:
	Array pQueue; //������� �����������
public:
	TQueue()
	{
		pQueue = Array();
	}

	Array getArray() { return pQueue; } //��������� ������

	int Size() //�������
	{
		return pQueue.Size();
	}

	void Clear()
	{
		pQueue.Clear();
	}

	void push(const T& value) //�������� ����� ���� ����
	{
		pQueue.push_back(value);
	}

	T pop() //������� ���� �����
	{
		T x;
		x = pQueue.remove(0);
		return x;
	}

	T& front() //��������� ���� �����
	{
		return pQueue[0];
	}

	bool Empty() //������?
	{
		return pQueue.Empty();
	}
};

#endif