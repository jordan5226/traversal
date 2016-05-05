/*
  Name: Breadth First Search (BFS)
  Copyright: Jordan Yeh
  Author: Jordan Yeh (jordan5226@gmail.com)
  Date: 04/05/16 09:08
  Description: Visit all nodes in a graph with BFS. Implement queue and list using STL.
  
        1
      /   \
    2      3
   / \    / \
  4   5  6   7
   \  |  |  /
       8
*/
#include <iostream>
#include <queue>
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
	
	vector<int> list[num_nodes];
	
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
	
	queue<int> bfsQueue; // BFS佇列 
	
	// TODO: do BFS
	int element = 0;
	bool node[num_nodes]; // 已走訪節點記錄 
	memset(node, 0, num_nodes);
	
	bfsQueue.push(1);							// (1)將起點放入佇列 
	cout<<"Output: ";
	while(true)
	{
		element = bfsQueue.front();				// (2)從佇列取出一元素
		bfsQueue.pop();
		if(!node[element-1]) // 若元素未走訪
		{
			cout<<element<<" ";					// 輸出元素 
			node[element-1] = true;				// 標記為已走訪 
			// 將該元素相鄰節點加入佇列
			vector<int>::iterator it = list[element-1].begin();
			++it;
			while(it != list[element-1].end())
			{
				if(!node[*it-1]) // 若節點未走訪 
				{
					bfsQueue.push(*it);
				}
				++it;
			}
		}

		if(bfsQueue.empty())					// (3)若BFS佇列為空則結束 
			break;
	}
	cout<<endl;
	
	system("pause");
	return 0;
}
