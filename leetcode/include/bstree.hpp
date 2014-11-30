/*
 * reference:
 * http://www.codeproject.com/Articles/602805/Creating-a-binary-search-tree-B
 * This source code is provided as part of article "using STL vectors to create Binary Search Trees (BST)" written
 * by Deepak Kumar Gupta. This file inherits the licence of CP Licence
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <stdio.h>

using namespace std;

// binary search tree
class bstree
{
	struct bst
	{
		unsigned int data;
		int leftIdx;
		int rightIdx;
		int nextIdx;
	};
	
public:
	bstree() {
	}
	
	vector<struct bst> _treedata;
	struct bst makeNode(unsigned int aData)
	{
		struct bst node = { aData, -1, -1 };
		return node;
	}

	void setleft(int currIndex, unsigned int aData)
	{
		int leftIndex = _treedata.size();
		_treedata[currIndex].leftIdx = leftIndex;		
		_treedata.push_back(makeNode(aData));
	}

	void setright(int currIndex, unsigned int aData)
	{
		int rightIndex = _treedata.size();
		_treedata[currIndex].rightIdx = rightIndex;
		_treedata.push_back(makeNode(aData));
	}

	void insert(unsigned int aData)
	{
		if(_treedata.size() == 0)
		{
			_treedata.push_back(makeNode(aData));
			return;
		}
		int currentIdx = 0;
		while ( currentIdx < _treedata.size() )
		{
			if(aData <= _treedata[currentIdx].data)
			{
				if( _treedata[currentIdx].leftIdx == -1)
				{
					setleft(currentIdx, aData);
					break;
				}
				else
					currentIdx = _treedata[currentIdx].leftIdx;
			}
			else
			{
				if(_treedata[currentIdx].rightIdx == -1)
				{
					setright(currentIdx, aData);
					break;
				}
				else
					currentIdx = _treedata[currentIdx].rightIdx;
			}
		}
	}

	void inTrav(int idx = 0)
	{
		if(_treedata[idx].leftIdx != -1)
			inTrav(_treedata[idx].leftIdx );
		cout<<_treedata[idx].data<<endl;
		if( _treedata[idx].rightIdx != -1)
			inTrav(_treedata[idx].rightIdx);
	}

	void preTrav(int idx = 0)
	{
		cout<<_treedata[idx].data<<endl;
		if(_treedata[idx].leftIdx != -1)
			preTrav(_treedata[idx].leftIdx );
		if( _treedata[idx].rightIdx != -1)
			preTrav(_treedata[idx].rightIdx);
	}
	void postTrav(int idx = 0)
	{
		if(_treedata[idx].leftIdx != -1)
			postTrav(_treedata[idx].leftIdx );
		if( _treedata[idx].rightIdx != -1)
			postTrav(_treedata[idx].rightIdx);
		cout<<_treedata[idx].data<<endl;
	}

	int max(int idx = 0)
	{
		if (-1 == idx) {
			return idx;
		} 
		while (-1 != _treedata[idx].rightIdx) {
			idx = _treedata[idx].rightIdx;
		}
		return idx;
	}
	int min(int idx = 0)
	{
		if (-1 == idx) {
			return idx;
		} 
		while (-1 != _treedata[idx].leftIdx) {
			idx = _treedata[idx].leftIdx;
		}
		return idx;
	}

	// 先push左子节点到栈，再push右子节点进栈，仅在出栈时访问即能保证 left, right, root 的后根遍历顺序
	// 要点在于，从栈中pop出的节点，如果右子树未访问，则要先进入右子树遍历
	// 是否遍历过右子树，可根据上次访问的节点，与本次访问的节点关系判断
	vector <unsigned int> postorderTraversal(int idx = 0)
	{
		stack<int> parents;
		vector<unsigned int> order;
		int lastVisited = -1;
		while(-1 != idx || parents.size() > 0) {
			if (-1 == idx) {
				idx = parents.top();
				parents.pop();

				if (-1 != _treedata[idx].rightIdx && _treedata[idx].rightIdx != lastVisited) {
					parents.push(idx);
					idx = _treedata[idx].rightIdx;
				}
				else {
					// visit
					lastVisited = idx;
					printf("%d ", _treedata[idx].data);
					order.push_back(_treedata[idx].data);
					idx = -1;
					continue;
				}
			}
			parents.push(idx);
			if (-1 != _treedata[idx].leftIdx) {
				idx = _treedata[idx].leftIdx;
			}
			else {
				idx = -1;
			}
		}
		printf("\n");
		return order;
	}

	// 先push左子节点入栈，如果左节点则访问pop出的节点。然后push刚才访问过的节点的右子节点入栈
	vector <unsigned int> inorderTraversal(int idx = 0)
	{
		stack<int> parents;
		vector<unsigned int> order;
		while(-1 != idx || parents.size() > 0) {
			if (idx == -1) {
				idx = parents.top();
				parents.pop();

				// visit
				printf("%d ", _treedata[idx].data);
				order.push_back(_treedata[idx].data);

				// next node
				idx = _treedata[idx].rightIdx;
				continue;
			}
		
			// push stack
			parents.push(idx);

			// next node
			idx = _treedata[idx].leftIdx;
		}
		printf("\n");
		return order;
	}

	// 先访问当前节点与左子节点，然后将右子节点入栈， 
	// 当到达最左节点时，pop栈中节点进行处理
	vector <unsigned int> preorderTraversal(int idx = 0)
	{
		stack<int> parents;
		vector<unsigned int> order;
		while(-1 != idx || parents.size() > 0) {
			if (idx == -1) {
				idx = parents.top();
				parents.pop();
			}
		
			// visit
			order.push_back(_treedata[idx].data);
			printf("%d ", _treedata[idx].data);

			// push stack
			if (-1 != _treedata[idx].rightIdx) {
				parents.push(_treedata[idx].rightIdx);
			}

			// next node
			idx = _treedata[idx].leftIdx;
		}
		printf("\n");
		return order;
	}

	/**
	 * @brief 保存二叉树中每层结点最左侧的结点
	 *
	 * key:tree depth, value:idx
	 * 执行connect()函数时会被赋值
	 */
	map<unsigned int, int> _listNextRight;

	/**
	 * @brief 按层输出二叉树的节点，每层从左向右输出
	 * @param depth:从第几层开始输出，默认为0，即根节点为第0层
	 */
	void print_connect(int depth = 0) {
		printf("connect tree:\n");
		for(int i = depth; i < _listNextRight.size(); i++) {
			int cur = _listNextRight[i];

			while (-1 != cur) {
				printf("%d ", _treedata[cur].data);
				cur = _treedata[cur].nextIdx;
			}
			printf("\n");
		}
		return;
	}

	/**
	 * @brief 链接二叉树各层的节点，每个节点的nextIdx即指向其相同深度的右侧节点
	 * @param idx:执行链接操作的起始节点位置，默认为0，即根节点
	 *
	 * https://oj.leetcode.com/problems/populating-next-right-pointers-in-each-node/
	 */
	void connect(int idx = 0) {
		unsigned int depth = 0;
		int nextIdx;
		unsigned int child_num = 0;
		queue<int> unvisited;

		if (-1 == idx) {
			return;
		}

		_listNextRight.clear();
		unvisited.push(idx);
		child_num = unvisited.size();
		nextIdx = -1;
		while (!unvisited.empty()) {
			int cur = unvisited.front();
			unvisited.pop();
			if (-1 != _treedata[cur].rightIdx) {
				unvisited.push(_treedata[cur].rightIdx);
			}
			if (-1 != _treedata[cur].leftIdx) {
				unvisited.push(_treedata[cur].leftIdx);
			}
			_treedata[cur].nextIdx = nextIdx;
			child_num--;
			if (child_num==0) {
				_listNextRight[depth++] = cur;
				nextIdx = -1;
				child_num = unvisited.size();
			}
			else {
				nextIdx = cur;
			}
		}
		return;
	}

	// 使用Queue 实现 BFS 广度优先遍历
	unsigned int maxDepthBfs(int idx = 0) 
	{
		unsigned int depth = 0;
		unsigned int child_num = 0;
		queue<int> unvisited;

		if (-1 == idx) {
			return 0;
		}

		unvisited.push(idx);
		child_num = unvisited.size();
		while (!unvisited.empty()) {
			int cur = unvisited.front();
			unvisited.pop();
			if (-1 != _treedata[cur].leftIdx) {
				unvisited.push(_treedata[cur].leftIdx);
			}
			if (-1 != _treedata[cur].rightIdx) {
				unvisited.push(_treedata[cur].rightIdx);
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
	unsigned int maxDepth(int idx = 0)
	{
		if (-1 == idx) {
			return 0;
		}
		unsigned int left = maxDepth(_treedata[idx].leftIdx);
		unsigned int right = maxDepth(_treedata[idx].rightIdx);
		return left > right ? (left+1) : (right+1);
	}

	bool isSameTree(vector <struct bst> &nodes_a, unsigned int idx_a, vector <struct bst>&nodes_b, unsigned int idx_b)
	{
		if ( -1 == idx_a || -1 == idx_b) {
			if (idx_a != idx_b) {
				return false;
			}
			else {
				return true;
			}
		}

		if (!isSameTree(nodes_a, nodes_a[idx_a].leftIdx, nodes_b, nodes_b[idx_b].leftIdx)) {
			return false;
		}
		if (nodes_a[idx_a].data != nodes_b[idx_b].data) {
			return false;
		}
		if (!isSameTree(nodes_a, nodes_a[idx_a].rightIdx, nodes_b, nodes_b[idx_b].rightIdx)) {
			return false;
		}
		
		return true;
	}

};

