#include "NotEqualExpressionNode.hpp"

#include <iostream>

NotEqualExpressionNode::NotEqualExpressionNode(ExpressionNode*& lhs,
                                               ExpressionNode*& rhs)
  : lhs(lhs)
  , rhs(rhs)
{}

void NotEqualExpressionNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "<>";
  rhs->emitSource("");
}

RegisterPool::Register NotEqualExpressionNode::emit()
{
  throw "not implemented NotEqualExpressionNode";
}
