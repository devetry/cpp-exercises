#include "int_list.hpp"
#include <memory>

IntList::Node::Node(int d, std::shared_ptr<Node> n): data{d}, next{n} {}
IntList::IntList(): head{nullptr} {}

void IntList::push_front(int val) {
  head = std::shared_ptr<Node>(new Node(val, head));
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
    head = head->next;
    return;
  }

  auto curr = head;
  while (curr != nullptr) {
    if (curr->next != nullptr && curr->next->data == val) break;
    curr = curr->next;
  }
  if (curr != nullptr && curr->next != nullptr && curr->next->data == val) {
    curr->next = curr->next->next;
  }
}