#ifndef LVALUE_NODE_HPP
#define LVALUE_NODE_HPP

#include "ExpressionNode.hpp" // for ExpressionNode

#include <memory> // for shared_ptr
#include <string> // for string
class Type;

class LvalueNode : public ExpressionNode
{
public:
  LvalueNode(std::shared_ptr<Type> type)
    : ExpressionNode(type)
  {}
  virtual std::string getId() = 0;
};

#endif
