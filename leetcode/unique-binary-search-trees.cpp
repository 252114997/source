/**
 * https://oj.leetcode.com/problems/unique-binary-search-trees/
 * Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
 *
 * For example,
 * Given n = 3, there are a total of 5 unique BST's. 
 *  1         3     3      2      1
 *   \       /     /      / \      \
 *    3     2     1      1   3      2
 *   /     /       \                 \
 *  2     1         2                 3
 *
 * 解：给出节点数，计算出这么多节点最多可能排列组合为几个BST树。
 * 解法可以这样理解，排序所有节点，任取一点为根，计算左子树可能有几种BST，再计算右子树可能有几种BST，
 * 左右子树的结果相乘即为结果。
 * 用乘法是因为，左右子树任意更改一个节点的位置即产生一颗新树。
 * 另外，根结点发生变化，又会产生一颗新树。一共有N个根，所以有N种可能，几种可能做加法。
 * 这里用到的知识其实是"组合组合"。
 */
#include <stdio.h>

int numTrees(int n)
{
  int sum = 0;
  if (0 >= n) {
    return 1;
  }
  if (1 == n) {
    return 1;
  }

  for(int i=0; i<n; i++) {
    int cur = 1;
    cur *= numTrees(i);
    cur *= numTrees(n-i-1);
    sum += cur;
  }
  return sum;
}

int main()
{
  for(int i=0; i<10; i++) {
    printf("numTrees(%d) == %d\n", i, numTrees(i));
  } 
}
