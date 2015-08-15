#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
};

ListNode* deleteDuplicates(ListNode* head) {
  if (head == NULL) return NULL;
  for (ListNode* prev = head, *cur = head->next; prev->next; cur = prev->next)
  {
    if (prev->val == cur->val)
    {
      prev->next = cur->next;
      delete cur;
    }
    else
    {
      prev = cur;
    }
  }
  return head;
}

int main() {

  ListNode *end = new ListNode{ 2, NULL };
  ListNode *e2 = new ListNode{ 1, end };
  ListNode *head = new ListNode{ 1, e2 };
  head = deleteDuplicates(head);

  ListNode *ptr = head;
  while(ptr) {
    std::cout << ptr->val << " -> ";
    ptr = ptr->next;
  }
  std::cout << "NULL";
  
  ptr = head;  
  while(ptr) { // Free memory
    ListNode *old = ptr;
    ptr = ptr->next;
    delete old;
  }

  return 0;
}