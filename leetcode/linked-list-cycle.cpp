/*
  https://oj.leetcode.com/problems/linked-list-cycle/
Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?

解：
使用HASH记录所有访问过的节点，如果发现新节点已经存在于HASH中，则说明链表存在循环。
如果不使用额外的HASH解决此问题，使用经典的龟兔赛跑算法，慢指针每次跑一次，快指针每次跑两步，如果快、慢指针相遇，则表明链表存在循环。

参考：
http://ostermiller.org/find_loop_singly_linked_list.html
*/

#include <stdio.h>
#include <map>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode (int x) :val(x), next(NULL) {}
};

bool hasCycle(ListNode *head)
{
  ListNode *low = head;;
  ListNode *fast = head->next;

  for(; low && fast; low = low->next) {
    if (low == fast) {
      printf("hasCycle low->val=%d\n", low->val);
      return true;
    }
    fast = fast->next;
    if (low == fast) {
      printf("hasCycle low->val=%d\n", low->val);
      return true;
    }
    if (NULL == fast) {
      printf("no Cycle\n");
      return false;
    }
    fast = fast->next;
  }
  printf("no Cycle\n");
  return false;
}

bool hasCycle_map(ListNode *head) 
{
  map<ListNode*, bool> visitedNodes;

  ListNode *parent = head;
  for(; parent->next != NULL; parent = parent->next) {
    ListNode *cur = parent->next;
    if (visitedNodes[cur]) { // because default value of map<ListNode*,bool> is 0(false)
      printf("hasCycle cur->val=%d\n", cur->val);
      return true;
    }
    visitedNodes[cur] = true;
  }
  printf("no Cycle\n");
  return false;
}

int insertNodePtr(ListNode *head,ListNode *newNode) 
{
  if (NULL == head || NULL == newNode) {
    printf("fail! NULL == head || NULL == newNode !\n");
    return -1;
  }

  ListNode *first = head->next;
  newNode->next = first;
  head->next = newNode;
  return 0;
}

int insertNode(ListNode *head, int val)
{
  ListNode *newNode = NULL;
  newNode = new ListNode(val);
  return insertNodePtr(head, newNode);
}
int deleteNode(ListNode *head, int val)
{
  ListNode *parent = head;

  for(; parent->next != NULL; parent = parent->next) {
    ListNode *cur = parent->next;
    if (cur->val != val) {
      continue;
    }
    ListNode *next = cur->next;
    parent->next = next;
    delete(cur);
    cur = NULL;
  }
}
int foreachNode(ListNode *head) 
{
  ListNode *parent = head;

  printf("head(%u) value list:\n", (unsigned int)head);
  for(; parent->next != NULL; parent = parent->next) {
    ListNode *cur = parent->next;
    printf("%d,", cur->val);
  }
  printf("\n");
}

int main()
{
  ListNode root(0);
  ListNode node(33);

  hasCycle(&root);
  insertNode(&root, 1);
  insertNode(&root, 2);
  insertNode(&root, 5);
  insertNodePtr(&root, &node);
  insertNode(&root, 4);
  insertNode(&root, 3);
  hasCycle(&root);
  insertNode(&root, 93);
  insertNode(&root, 8);
  insertNodePtr(&root, &node);
  insertNode(&root, 888);
  hasCycle(&root);

//  foreachNode(&root);

  return 0;
}
