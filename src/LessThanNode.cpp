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

Value LessThanNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto v_lhs = lhs->emit();
  auto v_rhs = rhs->emit();
  auto r_lhs = v_lhs.getTheeIntoARegister();
  auto r_rhs = v_rhs.getTheeIntoARegister();
  RegisterPool::Register result;

  std::cout << "slt " << result << ", " << r_lhs << ", " << r_rhs << '\n';

  return result;
}
