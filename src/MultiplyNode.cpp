#include "MultiplyNode.hpp"

#include <iostream>

MultiplyNode::MultiplyNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void MultiplyNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "*";
  rhs->emitSource("");
}

RegisterPool::Register MultiplyNode::emit()
{
  throw "not implemented";
}
