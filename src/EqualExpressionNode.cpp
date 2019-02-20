#include "EqualExpressionNode.hpp"

#include <iostream>

EqualExpressionNode::EqualExpressionNode(ExpressionNode*& lhs,
                                         ExpressionNode*& rhs)
  : lhs(lhs)
  , rhs(rhs)
{}

void EqualExpressionNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "=";
  rhs->emitSource("");
}

RegisterPool::Register EqualExpressionNode::emit()
{
  throw "not implemented";
}
