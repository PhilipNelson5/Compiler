#include "LessThanNode.hpp"

#include <iostream>

LessThanNode::LessThanNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(BooleanType::get())
  , lhs(left)
  , rhs(right)
{}

void LessThanNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "<";
  rhs->emitSource("");
}

RegisterPool::Register LessThanNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto r_lhs = lhs->emit();
  auto r_rhs = rhs->emit();
  RegisterPool::Register result;
  std::cout << "slt " << result << ", " << r_lhs << ", " << r_rhs << '\n';
  return result;
}
