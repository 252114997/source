/*
https://oj.leetcode.com/problems/maximum-depth-of-binary-tree/

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

解：
源码中的二叉树引用了http://www.codeproject.com/Articles/602805/Creating-a-binary-search-tree-B 
可用最简单的递归法解决；
或者广度优先遍历（BFS)

reference:
http://blog.csdn.net/ithomer/article/details/8799795
http://zh.wikipedia.org/wiki/%E6%B7%B1%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2
*/

/* ******************************************************************

This source code is provided as part of article "using STL vectors to create Binary Search Trees (BST)" written
by Deepak Kumar Gupta. This file inherits the licence of CP Licence

****************************************************************************/


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct bst
{
	unsigned int data;
	int leftIdx;
	int rightIdx;
};

void MakeNode(vector<struct bst> &v1, int aData)
{
	struct bst b1 = { aData, -1, -1 };
	v1.push_back(b1);
}

void setleft(vector<struct bst> &v1, int currIndex, int aData)
{
	unsigned int leftIndex = v1.size();
	v1[currIndex].leftIdx = leftIndex;
	struct bst b1 = { aData, -1, -1 };
	v1.push_back(b1);
}

void setright(vector<struct bst> &v1, int currIndex, int aData)
{
	unsigned int rightIndex = v1.size();
	v1[currIndex].rightIdx = rightIndex;
	struct bst b1 = { aData, -1, -1 };
	v1.push_back(b1);
}

void Insert(vector<struct bst> &v1, int aData)
{
	if(v1.size() == 0)
	{
		cout<<"Note is not made yet. MakeNode first..."<<endl;
		return;
	}
	unsigned int currentIdx = 0;
	while ( currentIdx < v1.size() )
	{
		if(aData <= v1[currentIdx].data)
		{
			if( v1[currentIdx].leftIdx == -1)
			{
				setleft(v1, currentIdx, aData);
				break;
			}
			else
				currentIdx = v1[currentIdx].leftIdx;
		}
		else
		{
			if(v1[currentIdx].rightIdx == -1)
			{
				setright(v1, currentIdx, aData);
				break;
			}
			else
				currentIdx = v1[currentIdx].rightIdx;
		}
	}
}

void InTrav(vector <struct bst> &v1, unsigned int Idx)
{
	if(v1[Idx].leftIdx != -1)
		InTrav(v1,v1[Idx].leftIdx );
	cout<<v1[Idx].data<<endl;
	if( v1[Idx].rightIdx != -1)
		InTrav(v1, v1[Idx].rightIdx);
}

void PreTrav(vector <struct bst> &v1, unsigned int Idx)
{
	cout<<v1[Idx].data<<endl;
	if(v1[Idx].leftIdx != -1)
		PreTrav(v1,v1[Idx].leftIdx );
	if( v1[Idx].rightIdx != -1)
		PreTrav(v1, v1[Idx].rightIdx);
}
void PostTrav(vector <struct bst> &v1, unsigned int Idx)
{
	if(v1[Idx].leftIdx != -1)
		PostTrav(v1,v1[Idx].leftIdx );
	if( v1[Idx].rightIdx != -1)
		PostTrav(v1, v1[Idx].rightIdx);
	cout<<v1[Idx].data<<endl;
}

// 使用Queue 实现 BFS 广度优先遍历
unsigned int MaxDepthBfs(vector <struct bst> &nodes, unsigned int Idx) 
{
	unsigned int depth = 0;
	unsigned int child_num = 0;
	queue<unsigned int> unvisited;

	if (-1 == Idx) {
		return 0;
	}

	unvisited.push(Idx);
	child_num = unvisited.size();
	while (!unvisited.empty()) {
		unsigned int cur = unvisited.front();
		unvisited.pop();
		if (-1 != nodes[cur].leftIdx) {
			unvisited.push(nodes[cur].leftIdx);
		}
		if (-1 != nodes[cur].rightIdx) {
			unvisited.push(nodes[cur].rightIdx);
		}

		child_num--;
		if (0 == child_num) { // child_num==0 时，表明已经完成树中某一层高度的所有节点的遍历,也就是又加深了一层
			depth++;
			child_num = unvisited.size();
		}
	}
	return depth;
}

// 使用递归实现 DFS 深度优先遍历
unsigned int MaxDepth(vector <struct bst> &nodes, unsigned int Idx)
{
	if (-1 == Idx) {
		return 0;
	}
	unsigned int left = MaxDepth(nodes, nodes[Idx].leftIdx);
	unsigned int right = MaxDepth(nodes, nodes[Idx].rightIdx);
	return left > right ? (left+1) : (right+1);
}

int main()
{
	vector <struct bst> v1;
	MakeNode(v1, 3);
	Insert(v1, 6);
	Insert(v1, 7);
	Insert(v1, 16);
	Insert(v1, 20);
	Insert(v1, 35);
	Insert(v1, 40);

	cout<<"InTrav:"<<endl;
	InTrav(v1, 0);
	cout<<"PreTrav:"<<endl;
	PreTrav(v1,0);
	cout<<"PostTrav:"<<endl;
	PostTrav(v1,0);

	cout<<"MaxDepth:"<<MaxDepth(v1, 0)<<endl;
	cout<<"MaxDepthBFS:"<<MaxDepthBfs(v1, 0)<<endl;

	return 0;
}


