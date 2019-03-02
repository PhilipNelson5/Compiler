#include "EqualExpressionNode.hpp"

#include <iostream>

EqualExpressionNode::EqualExpressionNode(ExpressionNode*& lhs,
                                         ExpressionNode*& rhs)
  : ExpressionNode(BooleanType::get())
  , lhs(lhs)
  , rhs(rhs)
{}

void EqualExpressionNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "=";
  rhs->emitSource("");
}

RegisterPool::Register EqualExpressionNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto r_lhs = lhs->emit();
  auto r_rhs = rhs->emit();
  RegisterPool::Register result;
  std::cout << "########################" << std::endl;
  std::cout << "# not sure how to do < #" << std::endl;
  std::cout << "########################" << std::endl;
  std::cout << "li " << result << ", 0" << std::endl;

  return result;
}
