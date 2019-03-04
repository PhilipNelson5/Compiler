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

Value GreaterThanNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto v_lhs = lhs->emit();
  auto v_rhs = rhs->emit();
  RegisterPool::Register result;
  auto r_lhs = v_lhs.getTheeIntoARegister();
  auto r_rhs = v_rhs.getTheeIntoARegister();

  std::cout << "sgt " << result << ", " << r_lhs << ", " << r_rhs << '\n';

  return result;
}
