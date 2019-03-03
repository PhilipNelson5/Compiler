#include "GreaterThanNode.hpp"

#include <iostream>

GreaterThanNode::GreaterThanNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(BooleanType::get())
  , lhs(left)
  , rhs(right)
{}

void GreaterThanNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << ">";
  rhs->emitSource("");
}

RegisterPool::Register GreaterThanNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto r_lhs = lhs->emit();
  auto r_rhs = rhs->emit();
  RegisterPool::Register result;
  std::cout << "sgt " << result << ", " << r_lhs << ", " << r_rhs << '\n';

  return result;
}
