/**
 * @brief 
 * 
 * Given a binary tree 
    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }



Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note: 
•You may only use constant extra space.
•You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).


For example,
 Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7



After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL


解：
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

