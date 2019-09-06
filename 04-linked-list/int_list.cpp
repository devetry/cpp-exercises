#include "int_list.hpp"

IntList::Node::Node(int d, Node* n): data{d}, next{n} {}
IntList::Node::~Node() {
  if (next != nullptr) delete next;
}
IntList::IntList(): head{nullptr} {}

IntList::~IntList() {
  if (head != nullptr) delete head;
}

void IntList::push_front(int val) {
  auto n = new Node(val, head);
  head = n;
}

bool IntList::contains(int val) const {
  auto curr = head;
  while (curr != nullptr) {
    if (curr->data == val) return true;
    curr = curr->next;
  }
  return false;
}

void IntList::remove(int val) {
  if (head != nullptr && head->data == val) {
    auto nodeToDelete = head;
    head = head->next;
    delete nodeToDelete;
    return;
  }

  auto curr = head;
  while (curr != nullptr) {
    if (curr->next != nullptr && curr->next->data == val) break;
    curr = curr->next;
  }
  if (curr != nullptr && curr->next != nullptr && curr->next->data == val) {
    auto nodeToDelete = curr->next;
    curr->next = curr->next->next;
    delete nodeToDelete;
  }
}