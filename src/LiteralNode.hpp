#ifndef LITERAL_NODE_HPP
#define LITERAL_NODE_HPP

#include "ExpressionNode.hpp" // for ExpressionNode

class LiteralNode : public ExpressionNode
{
public:
  LiteralNode(std::shared_ptr<Type> type)
    : ExpressionNode(type)
  {}

  virtual bool isConstant() const override { return true; }

  virtual bool isLiteral() const override { return true; }
};

#endif
