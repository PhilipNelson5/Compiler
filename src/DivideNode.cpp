#include "DivideNode.hpp"

#include <iostream>

DivideNode::DivideNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void DivideNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "/";
  rhs->emitSource("");
}

RegisterPool::Register DivideNode::emit()
{
  throw "not implemented DivideNode";
}
