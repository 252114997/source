/*
 * https://oj.leetcode.com/problems/binary-tree-preorder-traversal/
 * Given a binary tree, return the preorder traversal of its nodes' values.
 *
 * For example:
 * Given binary tree {1,#,2,3},
 *
 *  1
 *   \
 *    2
 *   /
 *  3
 *
 *
 *
 * return [1,2,3]. 
 *
 * Note: Recursive solution is trivial, could you do it iteratively?
 *
 *
 * 解：
 * TODO
 *
 * reference:
 * http://www.codeproject.com/Articles/602805/Creating-a-binary-search-tree-B
 * This source code is provided as part of article "using STL vectors to create Binary Search Trees (BST)" written
 * by Deepak Kumar Gupta. This file inherits the licence of CP Licence
 */


#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <stdio.h>

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

int Max(vector <struct bst> &v1, int Idx)
{
	if (-1 == Idx) {
		return Idx;
	} 
	while (-1 != v1[Idx].rightIdx) {
		Idx = v1[Idx].rightIdx;
	}
	return Idx;
}
int Min(vector <struct bst> &v1, int Idx)
{
	if (-1 == Idx) {
		return Idx;
	} 
	while (-1 != v1[Idx].leftIdx) {
		Idx = v1[Idx].leftIdx;
	}
	return Idx;
}

// 先push左子节点到栈，再push右子节点进栈，仅在出栈时访问即能保证 left, right, root 的后根遍历顺序
// 要点在于，从栈中pop出的节点，如果右子树未访问，则要先进入右子树遍历
// 是否遍历过右子树，可根据上次访问的节点，与本次访问的节点关系判断
vector <unsigned int> postorderTraversal(vector<struct bst> &v1, int Idx)
{
	stack<int> parents;
	vector<unsigned int> order;
	int lastVisited = -1;
	while(-1 != Idx || parents.size() > 0) {
		if (-1 == Idx) {
			Idx = parents.top();
			parents.pop();

			if (-1 != v1[Idx].rightIdx && v1[Idx].rightIdx != lastVisited) {
				parents.push(Idx);
				Idx = v1[Idx].rightIdx;
			}
			else {
				// visit
				lastVisited = Idx;
				printf("%d ", v1[Idx].data);
				order.push_back(v1[Idx].data);
				Idx = -1;
				continue;
			}
		}
		parents.push(Idx);
		if (-1 != v1[Idx].leftIdx) {
			Idx = v1[Idx].leftIdx;
		}
		else {
			Idx = -1;
		}
	}
	printf("\n");
	return order;
}

// 先push左子节点入栈，如果左节点则访问pop出的节点。然后push刚才访问过的节点的右子节点入栈
vector <unsigned int> inorderTraversal(vector<struct bst> &v1, int Idx)
{
	stack<int> parents;
	vector<unsigned int> order;
	while(-1 != Idx || parents.size() > 0) {
		if (Idx == -1) {
			Idx = parents.top();
			parents.pop();

			// visit
			printf("%d ", v1[Idx].data);
			order.push_back(v1[Idx].data);

			// next node
			Idx = v1[Idx].rightIdx;
			continue;
		}
	
		// push stack
		parents.push(Idx);

		// next node
		Idx = v1[Idx].leftIdx;
	}
	printf("\n");
	return order;
}

// 先访问当前节点与左子节点，然后将右子节点入栈， 
// 当到达最左节点时，pop栈中节点进行处理
vector <unsigned int> preorderTraversal(vector<struct bst> &v1, int Idx)
{
	stack<int> parents;
	vector<unsigned int> order;
	while(-1 != Idx || parents.size() > 0) {
		if (Idx == -1) {
			Idx = parents.top();
			parents.pop();
		}
	
		// visit
		order.push_back(v1[Idx].data);
		printf("%d ", v1[Idx].data);

		// push stack
		if (-1 != v1[Idx].rightIdx) {
			parents.push(v1[Idx].rightIdx);
		}

		// next node
		Idx = v1[Idx].leftIdx;
	}
	printf("\n");
	return order;
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

bool isSameTree(vector <struct bst> &nodes_a, unsigned int Idx_a, vector <struct bst>&nodes_b, unsigned int Idx_b)
{
	if ( -1 == Idx_a || -1 == Idx_b) {
		if (Idx_a != Idx_b) {
			return false;
		}
		else {
			return true;
		}
	}

	if (!isSameTree(nodes_a, nodes_a[Idx_a].leftIdx, nodes_b, nodes_b[Idx_b].leftIdx)) {
		return false;
	}
	if (nodes_a[Idx_a].data != nodes_b[Idx_b].data) {
		return false;
	}
	if (!isSameTree(nodes_a, nodes_a[Idx_a].rightIdx, nodes_b, nodes_b[Idx_b].rightIdx)) {
		return false;
	}
	
	return true;
}

int main()
{
	vector <struct bst> v1;
	MakeNode(v1, 3);
	Insert(v1, 6);
	Insert(v1, 7);
	Insert(v1, 30);
	Insert(v1, 40);
	Insert(v1, 20);
	Insert(v1, 16);
	Insert(v1, 45);
	Insert(v1, 55);

	cout<<"InTrav:"<<endl;
	InTrav(v1, 0);
	cout<<"PreTrav:"<<endl;
	PreTrav(v1,0);
	cout<<"PostTrav:"<<endl;
	PostTrav(v1,0);

	cout<<"preordertraversal:"<<endl;
	preorderTraversal(v1, 0);
	//preorderTraversal(v1, -1);
	cout<<"inordertraversal:"<<endl;
	inorderTraversal(v1, 0);
	//inorderTraversal(v1, -1);
	cout<<"portordertraversal:"<<endl;
	postorderTraversal(v1, 0);
	//postorderTraversal(v1, -1);
	
	return 0;
}


