#include "AndNode.hpp"

#include "Type.hpp"
#include <iostream>

AndNode::AndNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(BooleanType::get())
  , lhs(left)
  , rhs(right)
{}

void AndNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "&";
  rhs->emitSource("");
}

Value AndNode::emit()
{
  auto v_lhs = lhs->emit();
  auto v_rhs = rhs->emit();
  auto r_lhs = v_lhs.getTheeIntoARegister();
  auto r_rhs = v_rhs.getTheeIntoARegister();
  RegisterPool::Register result;

  fmt::print("and {}, {}, {}\n", result, r_lhs, r_rhs);

  return result;
}
