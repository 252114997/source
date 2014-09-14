/*
 * =============================================================================
 *
 *       Filename:  rbtree-tst.c
 *
 *    Description:  rbtree testcase.
 *
 *        Created:  09/02/2012 11:39:34 PM
 *
 *         Author:  Fu Haiping (forhappy), haipingf@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */

#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct mynode {
  	struct rb_node node;
  	char *string;
};

struct rb_root mytree = RB_ROOT;

struct mynode * my_search_n(struct rb_root *root, int n)
{
  	struct rb_node *node = root->rb_node;

	if (NULL == node) {
		return NULL;
	}
	if (n<=0 || n>rb_node_size(node)) {
		return NULL;
	}
	while (NULL != node) {
		int left_size = rb_node_size(node->rb_left);
		if (n <= left_size) {
			node = node->rb_left;
		}
		else if (n == left_size + 1) {
  			struct mynode *data = container_of(node, struct mynode, node);
			return data;
		}
		else {//if (n > left_size +1) {
			node = node->rb_right;
			n = n - left_size - 1;
		}
	}
	printf("never go here. n=%d\n", n);
	exit(0);
}

struct mynode * my_search(struct rb_root *root, char *string)
{
  	struct rb_node *node = root->rb_node;

  	while (node) {
  		struct mynode *data = container_of(node, struct mynode, node);
		int result;

		result = strcmp(string, data->string);

		if (result < 0)
  			node = node->rb_left;
		else if (result > 0)
  			node = node->rb_right;
		else
  			return data;
	}
	return NULL;
}

int my_insert(struct rb_root *root, struct mynode *data)
{
  	struct rb_node **new = &(root->rb_node), *parent = NULL;

  	/* Figure out where to put new node */
  	while (*new) {
  		struct mynode *this = container_of(*new, struct mynode, node);
  		int result = strcmp(data->string, this->string);

		parent = *new;
  		if (result < 0)
  			new = &((*new)->rb_left);
  		else if (result > 0)
  			new = &((*new)->rb_right);
  		else
  			return 0;
  	}

  	/* Add new node and rebalance tree. */
  	rb_link_node(&data->node, parent, new);
  	rb_insert_color(&data->node, root);

	return 1;
}

void my_free(struct mynode *node)
{
	if (node != NULL) {
		if (node->string != NULL) {
			free(node->string);
			node->string = NULL;
		}
		free(node);
		node = NULL;
	}
}

void print_ldr(struct rb_node *root)
{
	if (NULL == root)
	{
		return;
	}
	print_ldr(root->rb_left);
    printf("%s ", rb_entry(root, struct mynode, node)->string);  
	print_ldr(root->rb_right);
}

void print_root_size(struct rb_root *root) 
{
	printf("size=%lu\n", rb_node_size(root->rb_node));
}

#define NUM_NODES 32
int main()
{
	struct mynode *mn[NUM_NODES];

	/* *insert */
	int i = 0;
	printf("insert node from 1 to NUM_NODES(32): \n");
	for (; i < NUM_NODES; i++) {
		mn[i] = (struct mynode *)malloc(sizeof(struct mynode));
		mn[i]->string = (char *)malloc(sizeof(char) * 4);
		sprintf(mn[i]->string, "%d", i);
		my_insert(&mytree, mn[i]);
		//print_root_size(&mytree);
	}
	
	/* *search */
	struct rb_node *node;
	printf("search all nodes: \n");
	for (node = rb_first(&mytree); node; node = rb_next(node))
		printf("%s ", rb_entry(node, struct mynode, node)->string);
	printf("\n");

	print_ldr(mytree.rb_node);
	printf("\n");
	
	/* search n */
	for (i=1; i <= NUM_NODES; i++) {
		struct mynode *data = my_search_n(&mytree, i);
		if (data) {
			printf("the number %d data is %s \n", i, data->string);
		}
		else {
			printf("not found the number %d data.\n", i);
		}
	}

	/* *delete */
	printf("delete node 20: \n");
	struct mynode *data = my_search(&mytree, "20");
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}

	/* *delete again*/
	printf("delete node 10: \n");
	data = my_search(&mytree, "10");
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}

	/* *delete once again*/
	printf("delete node 15: \n");
	data = my_search(&mytree, "15");
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}

	/* *search again*/
	printf("search again:\n");
	for (node = rb_first(&mytree); node; node = rb_next(node))
		printf("key = %s\n", rb_entry(node, struct mynode, node)->string);
	return 0;
}


