#ifndef LVALUE_NODE_HPP
#define LVALUE_NODE_HPP

#include "ExpressionNode.hpp"

class LvalueNode : public ExpressionNode
{
public:
  LvalueNode(std::shared_ptr<Type> type)
    : ExpressionNode(type)
  {}
  virtual std::string getId() = 0;
};

#endif
