#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

#include <memory>

template<typename T>
class ListNode
{
public:
  ListNode(T* data)
    : data(std::shared_ptr<T>(data))
    , next(nullptr)
  {}

  ListNode(T* data, ListNode<T>* next)
    : data(std::shared_ptr<T>(data))
    , next(std::shared_ptr<ListNode<T>>(next))
  {}

  std::shared_ptr<T> data;

  std::shared_ptr<ListNode<T>> next;
};

#endif
