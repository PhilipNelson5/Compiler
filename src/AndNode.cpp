#include "AndNode.hpp"

#include <iostream>

AndNode::AndNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(BooleanType::get())
  , lhs(left)
  , rhs(right)
{}

void AndNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "&";
  rhs->emitSource("");
}

RegisterPool::Register AndNode::emit()
{
  throw "not implemented AndNode";
}
