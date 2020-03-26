// THIS FILE SHOULD NOW BE IRRELEVANT NOW THAT WE ARE USING A TEMPLATE CLASS

// #include "int_list.hpp"
// #include <memory>
// using namespace std;

// template <typename T>
// IntList<T>::Node::Node(T d, shared_ptr<Node> n):
//     data{d},
//     next{n}
// {};


// template <typename T>
// void IntList<T>::push_front(T val)
// {
//     auto valToInsert = make_shared<IntList::Node>(val, head);
//     head = valToInsert;
// }

// template <typename T>
// bool IntList<T>::contains(T val) const
// {
//     auto currentNode = head;
//     while (currentNode != nullptr)
//     {
//         if (currentNode->data == val) 
//         {
//             return true;
//         }
//         currentNode = currentNode->next;
//     }
//     return false;
// }

// template <typename T>
// bool IntList<T>::remove(T val)
// {
//     if (head->data == val)
//     {
//         head = head->next;
//         return true;
//     }

//     auto currentNode = head;
//     while (currentNode != nullptr)
//     {
//         if (currentNode->next->data == val) 
//         {
//             currentNode->next = currentNode->next->next;
//             return true;
//         }
//     }
//     return false;
// }