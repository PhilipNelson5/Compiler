#include "SubtractNode.hpp"

#include "IntegerLiteralNode.hpp"
#include "log/easylogging++.h"

#include <iostream>

SubtractNode::SubtractNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , lhs(left)
  , rhs(right)
{}

void SubtractNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "-";
  rhs->emitSource("");
}

Value SubtractNode::emit()
{
  if (lhs->type != rhs->type)
  {
    LOG(ERROR) << "mismatched types in subtract expression: "
               << lhs->type->name() << " and " << rhs->type->name();
  }

  if (lhs->type != IntegerType::get())
  {
    LOG(ERROR) << "can not subtract non integer types";
  }

  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  if (lhs->isConstant())
  {
    auto lhs_const = dynamic_cast<IntegerLiteralNode*>(lhs.get());
    auto v_rhs = rhs->emit();
    auto r_rhs = v_rhs.getTheeIntoARegister();
    RegisterPool::Register result;
    std::cout << "sub " << result << ", " << lhs_const->value << ", " << r_rhs
              << " # ";
    emitSource("");
    std::cout << std::endl;

    return result;
  }
  else if (rhs->isConstant())
  {
    auto rhs_const = dynamic_cast<IntegerLiteralNode*>(rhs.get());
    auto v_lhs = lhs->emit();
    auto r_lhs = v_lhs.getTheeIntoARegister();
    RegisterPool::Register result;
    std::cout << "sub " << result << ", " << r_lhs << ", " << rhs_const->value
              << " # ";
    emitSource("");
    std::cout << std::endl;

    return result;
  }
  else
  {
    auto v_lhs = lhs->emit();
    auto v_rhs = rhs->emit();
    auto r_lhs = v_lhs.getTheeIntoARegister();
    auto r_rhs = v_rhs.getTheeIntoARegister();
    RegisterPool::Register result;
    std::cout << "sub " << result << ", " << r_lhs << ", " << r_rhs << " # ";
    emitSource("");
    std::cout << std::endl;

    return result;
  }
}
