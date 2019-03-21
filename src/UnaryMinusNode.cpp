#include "UnaryMinusNode.hpp"

#include "Type.hpp"
#include <iostream>

UnaryMinusNode::UnaryMinusNode(ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , rhs(right)
{}

void UnaryMinusNode::emitSource(std::string indent)
{
  std::cout << indent;
  std::cout << "-";
  rhs->emitSource("");
}

Value UnaryMinusNode::emit()
{
  auto v_rhs = rhs->emit();
  auto r_rhs = v_rhs.getTheeIntoARegister();
  RegisterPool::Register result;

  fmt::print("subu {}, $0, {}\n", result, r_rhs);

  return result;
}
