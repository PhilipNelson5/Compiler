#include "DivideNode.hpp"

#include "IntegerLiteralNode.hpp"
#include "log/easylogging++.h"

#include <iostream>

DivideNode::DivideNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , lhs(left)
  , rhs(right)
{}

void DivideNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "/";
  rhs->emitSource("");
}

Value DivideNode::emit()
{
  if (lhs->type != rhs->type)
  {
    LOG(ERROR) << "mismatched types in divide expression: " << lhs->type->name()
               << " and " << rhs->type->name();
  }

  if (lhs->type != IntegerType::get())
  {
    LOG(ERROR) << "can not divide non integer types";
  }

  std::cout << "# ";
  emitSource("");
  std::cout << '\n';

  auto v_lhs = lhs->emit();
  auto v_rhs = rhs->emit();
  auto r_lhs = v_lhs.getTheeIntoARegister();
  auto r_rhs = v_rhs.getTheeIntoARegister();
  RegisterPool::Register result;

  std::cout << "div " << r_lhs << ", " << r_rhs << '\n';
  std::cout << "mflo " << result << " # ";
  emitSource("");
  std::cout << '\n';

  return result;
}
