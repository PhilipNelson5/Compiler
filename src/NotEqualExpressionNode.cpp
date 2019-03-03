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

RegisterPool::Register NotEqualExpressionNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto r_lhs = lhs->emit();
  auto r_rhs = rhs->emit();
  RegisterPool::Register result;
  std::cout << "sne " << result << ", " << r_lhs << ", " << r_rhs << '\n';

  return result;
}
