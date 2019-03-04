#include "AddNode.hpp"

#include "IntegerLiteralNode.hpp"
#include "log/easylogging++.h"

#include <iostream>

AddNode::AddNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , lhs(left)
  , rhs(right)
{}

void AddNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "+";
  rhs->emitSource("");
}

RegisterPool::Register AddNode::emit()
{
  if (lhs->type != rhs->type)
  {
    LOG(ERROR) << "mismatched types in add expression: " << lhs->type->name()
               << " and " << rhs->type->name();
  }

  if (lhs->type != IntegerType::get())
  {
    LOG(ERROR) << "can not add non integer types";
  }

  std::cout << "# ";
  emitSource("");
  std::cout << '\n';

  if (lhs->isConstant())
  {
    auto lhs_const = dynamic_cast<IntegerLiteralNode*>(lhs.get());
    auto r_rhs = rhs->emit();
    RegisterPool::Register result;
    std::cout << "add " << result << ", " << lhs_const->value << ", " << r_rhs
              << " # ";
    emitSource("");
    std::cout << '\n';

    return result;
  }
  else if (rhs->isConstant())
  {
    auto rhs_const = dynamic_cast<IntegerLiteralNode*>(rhs.get());
    auto r_lhs = lhs->emit();
    RegisterPool::Register result;
    std::cout << "add " << result << ", " << r_lhs << ", " << rhs_const->value
              << " # ";
    emitSource("");
    std::cout << '\n';

    return result;
  }
  else
  {
    auto r_lhs = lhs->emit();
    auto r_rhs = rhs->emit();
    RegisterPool::Register result;
    std::cout << "add " << result << ", " << r_lhs << ", " << r_rhs << " # ";
    emitSource("");
    std::cout << '\n';

    return result;
  }
}
