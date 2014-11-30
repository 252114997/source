/**
 * @brief https://oj.leetcode.com/problems/populating-next-right-pointers-in-each-node/
 * 
 *  Given a binary tree 
 *     struct TreeLinkNode {
 *       TreeLinkNode *left;
 *       TreeLinkNode *right;
 *       TreeLinkNode *next;
 *     }
 * 
 * 
 * 
 * Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
 * 
 * Initially, all next pointers are set to NULL.
 * 
 * Note: 
 * ?You may only use constant extra space.
 * ?You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
 * 
 * 
 * For example,
 *  Given the following perfect binary tree,
 * 
 *          1
 *        /  \
 *       2    3
 *      / \  / \
 *     4  5  6  7
 * 
 * 
 * 
 * After calling your function, the tree should look like:
 * 
 *          1 -> NULL
 *        /  \
 *       2 -> 3 -> NULL
 *      / \  / \
 *     4->5->6->7 -> NULL
 * 
 * 
 * 解：
 * 只要在遍历树节点时知道当前节点的depth即可将其链接到一起。
 * 不过无论preorder、inorder、postorder，都是先访问left再访问right，但题目要求从left链接到next中，
 * 所以比较方便的方法是先访问right，再访问left，这样每次只需要将当前节点的next指针指向上一次访问的节点即可。
 * 另外，bfs或dfs遍历都可以实现，我用的是bfs
 */

#include <vector>
#include <stdio.h>

#include "include/bstree.hpp"
int main()
{
    bstree tree;
    tree.insert(30);
    tree.insert(13);
    tree.insert(3);
    tree.insert(6);
    tree.insert(7);
    tree.insert(40);
    tree.insert(20);
    tree.insert(16);
    tree.insert(45);
    tree.insert(55);

    cout<<"preordertraversal:"<<endl;
    tree.preorderTraversal(0);
    cout<<"inordertraversal:"<<endl;
    tree.inorderTraversal(0);
    cout<<"portordertraversal:"<<endl;
    tree.postorderTraversal(0);

    tree.connect();
    tree.print_connect();
        
    return 0;
}

