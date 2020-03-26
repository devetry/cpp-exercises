#ifndef _INT_LIST_H_
#define _INT_LIST_H_


#include <memory>
using namespace std;

template <typename T> class IntList {
private:
    class Node {
    public:
        Node() = delete;
        Node(T d, shared_ptr<Node> n): data{d}, next{n} {};
        T data;
        shared_ptr<Node> next = nullptr;
    };
    shared_ptr<Node> head = nullptr;
public:
    void push_front(T val)
    {
        auto valToInsert = make_shared<IntList::Node>(val, head);
        head = valToInsert;
    }
    bool contains(T val) const
    {
        auto currentNode = head;
        while (currentNode != nullptr)
        {
            if (currentNode->data == val) 
            {
                return true;
            }
            currentNode = currentNode->next;
        }
        return false;
    }
    bool remove(T val)
    {
        if (head->data == val)
        {
            head = head->next;
            return true;
        }

        auto currentNode = head;
        while (currentNode != nullptr)
        {
            if (currentNode->next->data == val) 
            {
                currentNode->next = currentNode->next->next;
                return true;
            }
        }
        return false;
    }
};

#endif