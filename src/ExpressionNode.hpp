#ifndef EXPRESSION_NODE_HPP
#define EXPRESSION_NODE_HPP

#include "Node.hpp" // for Node

#include <memory> // for shared_ptr

class Type;

class ExpressionNode : public Node
{
public:
  ExpressionNode(std::shared_ptr<Type> type);
  virtual bool isLiteral();
  virtual bool isConstant();
  std::shared_ptr<Type> type;
};

#endif
