#include "AddNode.hpp"

#include <iostream>

AddNode::AddNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void AddNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "+";
  rhs->emitSource("");
}

RegisterPool::Register AddNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto r_lhs = lhs->emit();
  auto r_rhs = lhs->emit();
  RegisterPool::Register res;
  std::cout << "add " << res << ", " << r_rhs << ", " << r_lhs << " # ";

  emitSource("");
  std::cout << std::endl;

  return res;
}
