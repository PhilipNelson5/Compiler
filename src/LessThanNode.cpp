#include "LessThanNode.hpp"

#include <iostream>

LessThanNode::LessThanNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void LessThanNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "<";
  rhs->emitSource("");
}

RegisterPool::Register LessThanNode::emit()
{
  throw "not implemented";
}
