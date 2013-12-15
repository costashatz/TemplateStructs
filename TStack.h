#ifndef T_STACK_H
#define T_STACK_H

//����� TStack: ���� ��������� ������� �� ���������� ������� ��� ����� ����������� (������ �� ����������� push_back(), Size(), remove(), Empty(), [])

template<class T, class Array = TArray<T>>
class TStack
{
private:
	Array pStack; //������� �����������
public:
	TStack()
	{
		pStack = Array();
	}

	Array getArray() { return pStack; } //��������� ������

	int Size() //�������
	{
		return pStack.Size();
	}

	void Clear()
	{
		pStack.Clear();
	}

	void push(const T& value) //�������� ����� ��� ������
	{
		pStack.push_back(value);
	}

	T pop() //������� ���� �����
	{
		T x;
		x = pStack.remove(pStack.Size()-1);
		return x;
	}

	T& top() //��������� ���� �����
	{
		return pStack[pStack.Size()-1];
	}

	bool Empty() //������?
	{
		return pStack.Empty();
	}
};

#endif