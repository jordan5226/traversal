/*
  Name: Depth First Search (DFS)
  Copyright: Jordan Yeh
  Author: Jordan Yeh (jordan5226@gmail.com)
  Date: 04/05/16 09:08
  Description: Visit all nodes in a graph with DFS.
  
        1
      /   \
    2      3
   / \    / \
  4   5  6   7
   \  |  |  /
       8
*/
#include <iostream>
#include <windows.h>
using namespace std;


template <typename T>
struct Node {
	T value;
	Node<T> *next;
};

template <typename T>
void insertNode(Node<T> **ptr, T value)
{
	Node<T> *newNode;
	if(*ptr == NULL)
	{
		newNode = (Node<T>*)malloc(sizeof(Node<T>));
		*ptr = newNode;
	}
	else
	{
		newNode = *ptr;
		while(newNode->next != NULL) // �`�����linked list���� 
		{
			newNode = newNode->next;
		}
		newNode->next = (Node<T>*)malloc(sizeof(Node<T>)); // �b���ݴ��J�s��Node 
		newNode = newNode->next;
	}
	newNode->value = value;
	newNode->next = NULL;
}

template <typename T>
void printList(Node<T> *ptr)
{
	while(ptr != NULL)
	{
		printf("%d->", ptr->value);
		ptr = ptr->next;
	}
	printf("NULL\n");
}

template <typename T>
class Stack {
public:
	Stack(int capacity)
	{
		this->capacity = capacity;
		this->top = -1;
		stack = (T*)malloc(capacity * sizeof(T));
	}
	
	~Stack()
	{
		free(stack);
	}
	
	bool isFull()
	{
		if(top < capacity-1)
			return false;
		return true;
	}
	
	bool isEmpty()
	{
		if(top < 0)
			return true;
		return false;
	}
	
	bool push(T element)
	{
		if(!isFull())
		{
			stack[++top] = element;
			return true;
		}
		return false;
	}
	
	T pop()
	{
		return stack[top--];
	}
	
	void print()
	{
		cout<<"Stack: ";
		for(int i=top;i>=0;--i)
			cout<<stack[i]<<" ";
		cout<<"END"<<endl;
	}

private:
	int capacity, top;
	T *stack;
};

int main()
{
	int num_nodes=0; // �`�I�ƶq 
	int value=0, i=0;
	char ch;
	
	// TODO: read file && create adjacency list
	FILE *fptr;
	fptr = fopen("adj_list.txt", "r");
	if(!fptr)
	{
		printf("File loaded error!\n");
		exit(1);
	}
	fscanf(fptr, "%d\n", &num_nodes);
	
	Node<int>* list[num_nodes];
	
	while(!feof(fptr))
	{
		list[i] = NULL;
		while(fscanf(fptr, "%d%c", &value, &ch))
		{
			insertNode(&list[i], value);
			if(ch=='\n' || feof(fptr))
				break;
		}
		++i;
	}
	fclose(fptr);
	
	Stack<int> *tmpStk = new Stack<int>(num_nodes+1); // �Ȧs��� 
	Stack<int> *dfsStk = new Stack<int>(num_nodes*(num_nodes-1)+1); // DFS��� 
	
	// TODO: do DFS
	int element=0;
	bool node[num_nodes]; // �w���X�`�I�O�� 
	memset(node, 0, num_nodes);
	
	dfsStk->push(1);						// (1)�N�_�I��J��� 
	cout<<"Output: ";
	while(1)
	{
		if(!dfsStk->isEmpty())
			element = dfsStk->pop();		// (2)�q��̼u�X���ݤ��� 
		else
			break;							// (3)�YDFS��̬��ūh���� 
		if(!node[element-1]) 				// I.�Y���ݤ��������X 
		{
			cout<<element<<" "; 			// ��X���� 
			node[element-1] = true; 		// �аO���w���X 
			// �N�Ӥ����۾F�`�I�[�J��� 
			Node<int> *ptr = list[element-1];
			ptr = ptr->next;
			while(ptr != NULL) // ���̬۾F��C���Ķ̌Ǳ��J�Ȧs��� 
			{
				if(!tmpStk->push(ptr->value))
					exit(1); // ��̤w��
				ptr = ptr->next;
			}
			while(!tmpStk->isEmpty()) // �M��q�Ȧs��̼u�X�A�A���JDFS��̡F�Y�i�F���H�ۤ϶��Ǳ��JDFS��̤��ĪG�C 
			{
				if(!dfsStk->push(tmpStk->pop()))
					exit(1); // ��̤w�� 
			}
		}
		//dfsStk->print();
	}
	cout<<endl;
	
	system("pause");
	return 0;
}
