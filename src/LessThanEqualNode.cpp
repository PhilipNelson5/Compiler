#include "LessThanEqualNode.hpp"

#include <iostream>

LessThanEqualNode::LessThanEqualNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void LessThanEqualNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "<=";
  rhs->emitSource("");
}

RegisterPool::Register LessThanEqualNode::emit()
{
  throw "not implemented LessThanEqualNode";
}
