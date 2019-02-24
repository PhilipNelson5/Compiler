#include "GreaterThanEqualNode.hpp"

#include <iostream>

GreaterThanEqualNode::GreaterThanEqualNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void GreaterThanEqualNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << ">=";
  rhs->emitSource("");
}

RegisterPool::Register GreaterThanEqualNode::emit()
{
  throw "not implemented";
}
