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
	
	Stack<int> *tmpStk = new Stack<int>(num_nodes-1); // 暫存堆棧 
	Stack<int> *dfsStk = new Stack<int>((num_nodes*(num_nodes-1))/2); // DFS堆棧 
	
	// TODO: do DFS
	int element=0;
	bool node[num_nodes]; // 已走訪節點記錄 
	memset(node, 0, num_nodes);
	
	dfsStk->push(1);						// (1)將起點放入堆棧 
	cout<<"Output: ";
	while(1)
	{
		element = dfsStk->pop(); 			// (2)從堆棧彈出頂端元素 
		if(!node[element-1]) 				// I.若頂端元素未走訪 
		{
			cout<<element<<" "; 			// 輸出元素 
			node[element-1] = true; 		// 標記為已走訪 
			// 將該元素相鄰節點加入堆棧 
			Node *ptr = list[element-1];
			ptr = ptr->next;
			while(ptr!=NULL) // 先依相鄰串列順序依序推入暫存堆棧 
			{
				if(!tmpStk->push(ptr->value))
					exit(1); // 堆棧已滿
				ptr = ptr->next;
			}
			while(!tmpStk->isEmpty()) // 然後從暫存堆棧彈出，再推入DFS堆棧；即可達成以相反順序推入DFS堆棧之效果。 
			{
				if(!dfsStk->push(tmpStk->pop()))
					exit(1); // 堆棧已滿 
			}
		}
		else								// II.若頂端元素已走訪 
		{
			if(dfsStk->isEmpty())			// (3)若DFS堆棧為空則結束 
				break;
		}
		//dfsStk->print();
	}
	cout<<endl;
	
	system("pause");
	return 0;
}
