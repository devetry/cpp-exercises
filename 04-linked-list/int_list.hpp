#include <memory>
class IntList {
public:
  IntList();
  void push_front(int);
  bool contains(int) const;
  void remove(int);

private:
  class Node {
  public:
    Node(int, std::shared_ptr<Node>);
    Node() = delete;

    int data;
    std::shared_ptr<Node> next;

  };
  std::shared_ptr<Node> head;
};