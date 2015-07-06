#include <cassert>
#include <array>
#include <iostream>

struct Node
{
  Node *next;
  int data;

  Node(int data) : data(data)
    {}
};

Node *merge_lists(Node *list1, Node *list2)
{
  assert(list2 != nullptr);

  Node *list, **pnext = &list;

  while (list1 != nullptr)
  {
    if (list1->data > list2->data)
      std::swap(list1, list2);

    *pnext = list1;
    pnext = &list1->next;
    list1 = *pnext;
  }

  *pnext = list2;

  return list;
}

Node *merge_sort_list(Node *list)
{
  std::array<Node *, 32> hooks = {};
  auto it_hook_end = hooks.begin();

  while (list != nullptr)
  {
    Node *next = list->next;
    list->next = nullptr;

    auto it_hook = hooks.begin();
    for (; it_hook != it_hook_end && *it_hook != nullptr; ++it_hook)
    {
      list = merge_lists(list, *it_hook);
      *it_hook = nullptr;
    }

    if (it_hook == it_hook_end)
      if (it_hook < hooks.end())
        it_hook = it_hook_end++;
      else
        --it_hook;

    assert(*it_hook == nullptr);
    *it_hook = list;

    list = next;
  }

  for (auto it_hook = hooks.begin(); it_hook != it_hook_end; ++it_hook)
    if (*it_hook != nullptr)
      list = merge_lists(list, *it_hook);

  return list;
}


int main() 
{
  Node *list = nullptr;

  Node *node = new Node(10);
  node->next = list;
  list = node;

  node = new Node(8);
  node->next = list;
  list = node;

  node = new Node(15);
  node->next = list;
  list = node;

  node = new Node(2);
  node->next = list;
  list = node;

  for (node = list; node != nullptr; node = node->next)
    std::cout << node->data << " ";

  std::cout << std::endl;

  list = merge_sort_list(list);

  for (node = list; node != nullptr; node = node->next)
    std::cout << node->data << " ";

  std::cout << std::endl;

    return 0;
}
