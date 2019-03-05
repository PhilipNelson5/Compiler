#include "NotEqualExpressionNode.hpp"

#include <iostream>

NotEqualExpressionNode::NotEqualExpressionNode(ExpressionNode*& lhs,
                                               ExpressionNode*& rhs)
  : ExpressionNode(BooleanType::get())
  , lhs(lhs)
  , rhs(rhs)
{}

void NotEqualExpressionNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "<>";
  rhs->emitSource("");
}

Value NotEqualExpressionNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto v_lhs = lhs->emit();
  auto v_rhs = rhs->emit();
  auto r_lhs = v_lhs.getTheeIntoARegister();
  auto r_rhs = v_rhs.getTheeIntoARegister();
  RegisterPool::Register result;

  std::cout << "sne " << result << ", " << r_lhs << ", " << r_rhs << '\n';

  return result;
}
