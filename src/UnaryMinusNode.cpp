#include "UnaryMinusNode.hpp"

#include <iostream>

UnaryMinusNode::UnaryMinusNode(ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , rhs(right)
{}

void UnaryMinusNode::emitSource(std::string indent)
{
  std::cout << indent;
  std::cout << "-";
  rhs->emitSource("");
}

Value UnaryMinusNode::emit()
{
  throw "not implemented UnaryMinusNode";
}
