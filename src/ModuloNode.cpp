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
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto r_lhs = lhs->emit();
  auto r_rhs = rhs->emit();
  RegisterPool::Register result;
  std::cout << "div " << r_lhs << ", " << r_rhs << std::endl;

  std::cout << "mfhi " << result << " # ";
  emitSource("");
  std::cout << std::endl;
  
  return result;
}
