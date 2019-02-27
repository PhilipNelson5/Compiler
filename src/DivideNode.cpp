#include "DivideNode.hpp"

#include <iostream>

DivideNode::DivideNode(ExpressionNode*& left, ExpressionNode*& right)
  : lhs(left)
  , rhs(right)
{}

void DivideNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "/";
  rhs->emitSource("");
}

RegisterPool::Register DivideNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto r_lhs = lhs->emit();
  auto r_rhs = rhs->emit();
  RegisterPool::Register result;
  std::cout << "div " << r_lhs << ", " << r_rhs << std::endl;

  std::cout << "mflo " << result << " # ";
  emitSource("");
  std::cout << std::endl;
  
  return result;
}
