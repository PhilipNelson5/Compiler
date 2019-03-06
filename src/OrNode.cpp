#include "OrNode.hpp"

#include <iostream>

OrNode::OrNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(BooleanType::get())
  , lhs(left)
  , rhs(right)
{}

void OrNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "|";
  rhs->emitSource("");
}

Value OrNode::emit()
{
  throw "not implemented OrNode";
}
