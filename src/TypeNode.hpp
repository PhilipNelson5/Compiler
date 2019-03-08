#ifndef TYPE_NODE_HPP
#define TYPE_NODE_HPP

#include <memory> // for shared_ptr

class Type;

class TypeNode
{
public:
  TypeNode(std::shared_ptr<Type> type)
    : type(type)
  {}

  std::shared_ptr<Type> type;
};
#endif
