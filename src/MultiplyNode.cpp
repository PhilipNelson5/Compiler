#include "MultiplyNode.hpp"

#include "IntegerLiteralNode.hpp"
#include "log/easylogging++.h"

#include <iostream>

MultiplyNode::MultiplyNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , lhs(left)
  , rhs(right)
{}

void MultiplyNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "*";
  rhs->emitSource("");
}

Value MultiplyNode::emit()
{
  if (lhs->type != rhs->type)
  {
    LOG(ERROR) << "mismatched types in multiply expression: "
               << lhs->type->name() << " and " << rhs->type->name();
  }

  if (lhs->type != IntegerType::get())
  {
    LOG(ERROR) << "can not multiply non integer types";
  }

  std::cout << "# ";
  emitSource("");
  std::cout << '\n';

  auto v_lhs = lhs->emit();
  auto v_rhs = rhs->emit();
  RegisterPool::Register result;
  auto r_lhs = v_lhs.getTheeIntoARegister();
  auto r_rhs = v_rhs.getTheeIntoARegister();

  std::cout << "mult " << r_lhs << ", " << r_rhs << '\n';
  std::cout << "mflo " << result << " # ";
  emitSource("");
  std::cout << '\n';

  return result;
}
