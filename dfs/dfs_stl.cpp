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
	
	vector<int> list[num_nodes]; // �Ϫ��۾F��C 
	
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
	
	stack<int> tmpStk, dfsStk; // �Ȧs��̡BDFS��� 
	
	// TODO: do DFS
	int element=0;
	bool node[num_nodes]; // �w���X�`�I�O�� 
	memset(node, 0, num_nodes);
	
	dfsStk.push(1);							// (1)�N�_�I��J��� 
	cout<<"Output: ";
	while(1)
	{
		if(!dfsStk.empty())
		{
			element = dfsStk.top();			// (2)�q��̼u�X���ݤ���
			dfsStk.pop();
		}
		else
			break;							// (3)�YDFS��̬��ūh���� 
		if(!node[element-1]) 				// I.�Y���ݤ��������X 
		{
			cout<<element<<" "; 			// ��X���� 
			node[element-1] = true; 		// �аO���w���X 
			// �N�Ӥ����۾F�`�I�[�J��� 
			vector<int>::iterator it = list[element-1].begin();
			++it;
			while(it!=list[element-1].end()) // ���̬۾F��C���Ķ̌Ǳ��J�Ȧs��� 
			{
				tmpStk.push(*it);
				++it;
			}
			while(!tmpStk.empty()) // �M��q�Ȧs��̼u�X�A�A���JDFS��̡F�Y�i�F���H�ۤ϶��Ǳ��JDFS��̤��ĪG�C 
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
