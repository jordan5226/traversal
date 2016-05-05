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

struct Node {
	int value;
	Node *next;
};

void insertNode(Node **ptr, int value)
{
	Node *newNode;
	if(*ptr == NULL)
	{
		newNode = (Node*)malloc(sizeof(Node));
		*ptr = newNode;
	}
	else
	{
		newNode = *ptr;
		while(newNode->next != NULL) // �`�����linked list���� 
		{
			newNode = newNode->next;
		}
		newNode->next = (Node*)malloc(sizeof(Node)); // �b���ݴ��J�s��Node 
		newNode = newNode->next;
	}
	newNode->value = value;
	newNode->next = NULL;
}

void printList(Node *ptr)
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
		if(top <0)
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
	
	// TODO: read file && create adjacency list
	FILE *fptr;
	fptr = fopen("adj_list.txt", "r");
	if(!fptr)
	{
		printf("File loaded error!\n");
		exit(1);
	}
	fscanf(fptr, "%d\n", &num_nodes);
	
	Node* list[num_nodes];
	
	while(!feof(fptr))
	{
		list[i]=NULL;
		while(((value = fgetc(fptr)) != '\n') && (value != EOF))
		{
			if(value == ' ')
				continue;
			insertNode(&list[i], value-48);
		}
		++i;
	}
	fclose(fptr);
	
	Stack<int> *tmpStk = new Stack<int>(num_nodes-1); // �Ȧs��� 
	Stack<int> *dfsStk = new Stack<int>((num_nodes*(num_nodes-1))/2); // DFS��� 
	
	// TODO: do DFS
	int element=0;
	bool node[num_nodes]; // �w���X�`�I�O�� 
	memset(node, 0, num_nodes);
	
	dfsStk->push(1);						// (1)�N�_�I��J��� 
	cout<<"Output: ";
	while(1)
	{
		element = dfsStk->pop(); 			// (2)�q��̼u�X���ݤ��� 
		if(!node[element-1]) 				// I.�Y���ݤ��������X 
		{
			cout<<element<<" "; 			// ��X���� 
			node[element-1] = true; 		// �аO���w���X 
			// �N�Ӥ����۾F�`�I�[�J��� 
			Node *ptr = list[element-1];
			ptr = ptr->next;
			while(ptr!=NULL) // ���̬۾F��C���Ķ̌Ǳ��J�Ȧs��� 
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
		else								// II.�Y���ݤ����w���X 
		{
			if(dfsStk->isEmpty())			// (3)�YDFS��̬��ūh���� 
				break;
		}
		//dfsStk->print();
	}
	cout<<endl;
	
	system("pause");
	return 0;
}
