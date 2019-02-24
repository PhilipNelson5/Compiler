#include "SubtractNode.hpp"

#include <iostream>

SubtractNode::SubtractNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void SubtractNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "-";
  rhs->emitSource("");
}

RegisterPool::Register SubtractNode::emit()
{
  throw "not implemented SubtractNode";
}
