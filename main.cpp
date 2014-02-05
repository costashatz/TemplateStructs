#include <iostream>
#include "TArray.h"
#include "TBinaryTree.h"
#include "TDeque.h"
#include "TLinkedList.h"
using namespace std;

int main()
{
	cout<<"TArray example: \n";
	TArray<int> testArray;
	testArray.push_back(10);
	testArray.push_back(20);
	testArray.push_front(1);
	testArray.Clear();
	for(TArray<int>::iterator it=testArray.begin();it!=testArray.end();it++)
		cout<<*it<<endl;

	cout<<"TBinaryTree example: \n";
	TBinaryTree<int> tree;
	tree.addElement(20);
	tree.addElement(10);
	tree.addElement(40);
	tree.addElement(2);
	tree.addElement(12);
	tree.remove(10);
	tree.displayPreOrder();

	cout<<"TDeque example: \n";
	TDeque<int> deque;
	deque.push_back(10);
	deque.push_front(20);
	deque.push_front(30);
	deque.push_back(3);
	for(TDeque<int>::iterator it=deque.begin();it!=deque.end();it++)
		cout<<*it<<endl;
	cout<<"Show items without iterators:\n";
	for(int i=0;i<deque.Size();i++)
		cout<<deque[i]<<endl;

	TList<int> list;
	return 0;
}