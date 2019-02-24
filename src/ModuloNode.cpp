#include "ModuloNode.hpp"

#include <iostream>

ModuloNode::ModuloNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void ModuloNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "%";
  rhs->emitSource("");
}

RegisterPool::Register ModuloNode::emit()
{
  throw "not implemented ModuloNode";
}
