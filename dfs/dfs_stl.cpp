/*
  Name: Depth First Search (DFS)
  Copyright: Jordan Yeh
  Author: Jordan Yeh (jordan5226@gmail.com)
  Date: 04/05/16 09:08
  Description: Visit all nodes in a graph with DFS. Implements stack and list using STL.
  
        1
      /   \
    2      3
   / \    / \
  4   5  6   7
   \  |  |  /
       8
*/
#include <iostream>
#include <stack>
#include <vector>
#include <windows.h>
using namespace std;


int main()
{
	int num_nodes=0; // 節點數量 
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
	
	vector<int> list[num_nodes]; // 圖的相鄰串列 
	
	while(!feof(fptr))
	{
		while(fscanf(fptr, "%d%c", &value, &ch))
		{
			list[i].push_back(value);
			if(ch=='\n' || feof(fptr))
				break;
		}
		++i;
	}
	fclose(fptr);
	
	stack<int> tmpStk, dfsStk; // 暫存堆棧、DFS堆棧 
	
	// TODO: do DFS
	int element=0;
	bool node[num_nodes]; // 已走訪節點記錄 
	memset(node, 0, num_nodes);
	
	dfsStk.push(1);							// (1)將起點放入堆棧 
	cout<<"Output: ";
	while(1)
	{
		if(!dfsStk.empty())
		{
			element = dfsStk.top();			// (2)從堆棧彈出頂端元素
			dfsStk.pop();
		}
		else
			break;							// (3)若DFS堆棧為空則結束 
		if(!node[element-1]) 				// I.若頂端元素未走訪 
		{
			cout<<element<<" "; 			// 輸出元素 
			node[element-1] = true; 		// 標記為已走訪 
			// 將該元素相鄰節點加入堆棧 
			vector<int>::iterator it = list[element-1].begin();
			++it;
			while(it!=list[element-1].end()) // 先依相鄰串列順序依序推入暫存堆棧 
			{
				tmpStk.push(*it);
				++it;
			}
			while(!tmpStk.empty()) // 然後從暫存堆棧彈出，再推入DFS堆棧；即可達成以相反順序推入DFS堆棧之效果。 
			{
				dfsStk.push(tmpStk.top());
				tmpStk.pop();
			}
		}
	}
	cout<<endl;
	
	system("pause");
	return 0;
}
