#include "GreaterThanNode.hpp"

#include <iostream>

GreaterThanNode::GreaterThanNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void GreaterThanNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << ">";
  rhs->emitSource("");
}

RegisterPool::Register GreaterThanNode::emit()
{
  throw "not implemented GreaterThanNode";
}
