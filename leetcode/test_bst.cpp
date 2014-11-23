#include "include/bstree.hpp"

int main()
{
	bstree tree;
	tree.insert(3);
	tree.insert(6);
	tree.insert(7);
	tree.insert(30);
	tree.insert(40);
	tree.insert(20);
	tree.insert(16);
	tree.insert(45);
	tree.insert(55);

	cout<<"InTrav:"<<endl;
	tree.inTrav(0);
	cout<<"PreTrav:"<<endl;
	tree.preTrav(0);
	cout<<"PostTrav:"<<endl;
	tree.postTrav(0);

	cout<<"preordertraversal:"<<endl;
	tree.preorderTraversal(0);
	//preorderTraversal(v1, -1);
	cout<<"inordertraversal:"<<endl;
	tree.inorderTraversal(0);
	//inorderTraversal(v1, -1);
	cout<<"portordertraversal:"<<endl;
	tree.postorderTraversal(0);
	//postorderTraversal(v1, -1);
	
	return 0;
}

