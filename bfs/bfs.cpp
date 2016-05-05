/*
  Name: Breadth First Search (BFS)
  Copyright: Jordan Yeh
  Author: Jordan Yeh (jordan5226@gmail.com)
  Date: 04/05/16 09:08
  Description: Visit all nodes in a graph with BFS.
  
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
	int value;
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
class Queue {
public:
	Queue(int capacity)
	{
		this->capacity = capacity;
		this->front = capacity-1;
		this->rear = capacity-1;
		queue = (T*)malloc(capacity * sizeof(T));
	}
	~Queue()
	{
		free(queue);
	}
	
	bool isFull()
	{
		if((rear+1)%capacity == front)
			return true;
		return false;
	}
	
	bool isEmpty()
	{
		if(front == rear)
			return true;
		return false;
	}
	
	bool add(T element)
	{
		if(!isFull())
		{
			rear = (rear+1)%capacity;
			queue[rear] = element;
			return true;
		}
		return false;
	}
	
	T del()
	{
		if(!isEmpty())
		{
			front = (front+1)%capacity;
			return queue[front];
		}
		return -1;
	}
	
	void print()
	{
		cout<<"Queue: ";
		for(int i=(front+1)%capacity;i!=(rear+1)%capacity;i=(i+1)%capacity)
			cout<<queue[i]<<" "; 
		cout<<"END"<<endl;
	}

private:
	int capacity, front, rear;
	T *queue;
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
	
	Queue<int> *bfsQueue = new Queue<int>(num_nodes+1); // BFS��C 
	
	// TODO: do BFS
	int element = 0;
	bool node[num_nodes]; // �w���X�`�I�O�� 
	memset(node, 0, num_nodes);
	
	bfsQueue->add(1);							// (1)�N�_�I��J��C 
	cout<<"Output: ";
	while(true)
	{
		element = bfsQueue->del();				// (2)�q��C���X�@����
		if(!node[element-1]) // �Y���������X
		{
			cout<<element<<" "; 				// ��X���� 
			node[element-1] = true; 			// �аO���w���X 
			// �N�Ӥ����۾F�`�I�[�J��C
			Node<int> *ptr = list[element-1];
			ptr = ptr->next;
			while(ptr != NULL)
			{
				if(!node[ptr->value-1]) // �Y�`�I�����X 
				{
					if(!bfsQueue->add(ptr->value))
						exit(1); // ��C�w�� 
				}
				ptr = ptr->next;
			}
		}

		if(bfsQueue->isEmpty())					// (3)�YBFS��C���ūh���� 
			break;
		//bfsQueue->print();
	}
	cout<<endl;
	
	system("pause");
	return 0;
}
