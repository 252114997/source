/**
 * @brief https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
 * 
 * Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 *
 * 解：
 * 输入数据是已经排序的数据。输出数据是一个二叉树。
 * 基本过程是：
 * 取已排序数据的中值作为树根，
 * 然后整理小于中值的数据为二叉树，并使用返回的树根为左子节点，
 * 然后整理大于中值的数据为二叉树，并使用返回的树根为右子节点，
 * 
 * 使用实现上述过程，算法并不复杂
 */

#include <vector>
#include <stdio.h>

#include "include/bstree.hpp"
int main()
{
	// 构建测试数据
    vector<int> num;
    int count=1;
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);
    num.push_back(count++);

	// 生成bstree
    bstree tree;
    int rootIdx = tree.sortedArrayToBST(num);
	
	// 输出测试结果
	printf("rootIdx=%d\n", rootIdx);
	tree.iteraotrPrint();
	tree.inorderTraversal(rootIdx);

    cout<<"preordertraversal:"<<endl;
    tree.preorderTraversal(rootIdx);
    cout<<"inordertraversal:"<<endl;
    tree.inorderTraversal(rootIdx);
    cout<<"portordertraversal:"<<endl;
    tree.postorderTraversal(rootIdx);

    return 0;
}

