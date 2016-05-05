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
		while(newNode->next != NULL) // 循環找到linked list尾端 
		{
			newNode = newNode->next;
		}
		newNode->next = (Node*)malloc(sizeof(Node)); // 在尾端插入新的Node 
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
	int num_nodes=0; // 節點數量 
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
	
	Queue<int> *bfsQueue = new Queue<int>(num_nodes+1); // BFS佇列 
	
	// TODO: do BFS
	int element = 0;
	bool node[num_nodes]; // 已走訪節點記錄 
	memset(node, 0, num_nodes);
	
	bfsQueue->add(1); 							// (1)將起點放入佇列 
	cout<<"Output: ";
	while(true)
	{
		element = bfsQueue->del();				// (2)從佇列取出一元素
		if(!node[element-1]) // 若元素未走訪
		{
			cout<<element<<" "; 				// 輸出元素 
			node[element-1] = true; 			// 標記為已走訪 
			// 將該元素相鄰節點加入佇列
			Node *ptr = list[element-1];
			ptr = ptr->next;
			while(ptr != NULL)
			{
				if(!node[ptr->value-1]) // 若節點未走訪 
				{
					if(!bfsQueue->add(ptr->value))
						exit(1); // 佇列已滿 
				}
				ptr = ptr->next;
			}
		}

		if(bfsQueue->isEmpty())					// (3)若BFS佇列為空則結束 
			break;
		//bfsQueue->print();
	}
	cout<<endl;
	
	system("pause");
	return 0;
}
