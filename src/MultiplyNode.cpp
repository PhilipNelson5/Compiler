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
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto r_lhs = lhs->emit();
  auto r_rhs = rhs->emit();
  RegisterPool::Register result;
  std::cout << "mult " << r_lhs << ", " << r_rhs << std::endl;

  std::cout << "mflo " << result << " # ";
  emitSource("");
  std::cout << std::endl;
  
  return result;
}
