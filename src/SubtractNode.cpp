#include "SubtractNode.hpp"

#include <iostream>

SubtractNode::SubtractNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void SubtractNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "-";
  rhs->emitSource("");
}

RegisterPool::Register SubtractNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto r_lhs = lhs->emit();
  auto r_rhs = rhs->emit();
  RegisterPool::Register res;
  std::cout << "sub " << res << ", " << r_lhs << ", " << r_rhs << " # ";

  emitSource("");
  std::cout << std::endl;

  return res;
}
