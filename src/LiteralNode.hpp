#ifndef LITERAL_NODE_HPP
#define LITERAL_NODE_HPP

#include "ExpressionNode.hpp" // for ExpressionNode

class LiteralNode : public ExpressionNode
{
public:
  LiteralNode(std::shared_ptr<Type> type)
    : ExpressionNode(type)
  {}

  bool isConstant() { return true; }

  bool isLiteral() { return true; }
};

#endif
