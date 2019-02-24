#include "UnaryMinusNode.hpp"

#include <iostream>

UnaryMinusNode::UnaryMinusNode(ExpressionNode*& right)
  : rhs(right)
{}

void UnaryMinusNode::emitSource(std::string indent)
{
  std::cout << indent;
  std::cout << "~";
  rhs->emitSource("");
}

RegisterPool::Register UnaryMinusNode::emit()
{
  throw "not implemented UnaryMinusNode";
}
