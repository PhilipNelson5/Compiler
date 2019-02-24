#include "NotNode.hpp"

#include <iostream>

NotNode::NotNode(ExpressionNode*& right)
  : rhs(right)
{}

void NotNode::emitSource(std::string indent)
{
  std::cout << indent;
  std::cout << "~";
  rhs->emitSource("");
}

RegisterPool::Register NotNode::emit()
{
  throw "not implemented NotNode";
}
