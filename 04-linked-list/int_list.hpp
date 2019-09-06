class IntList {
public:
  IntList();
  ~IntList();
  void push_front(int);
  bool contains(int) const;
  void remove(int);

private:
  class Node {
  public:
    Node(int, Node*);
    Node() = delete;
    ~Node();

    int data;
    Node* next;

  };
  Node* head;
};