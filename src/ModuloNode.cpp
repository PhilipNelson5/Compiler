#include "ModuloNode.hpp"

#include "log/easylogging++.h"

#include <iostream>

ModuloNode::ModuloNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , lhs(left)
  , rhs(right)
{}

void ModuloNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "%";
  rhs->emitSource("");
}

RegisterPool::Register ModuloNode::emit()
{
  if (lhs->type != rhs->type)
  {
    LOG(ERROR) << "mismatched types in divide expression: "
               << lhs->type->name() << " and " << rhs->type->name();
  }

  if (lhs->type != IntegerType::get())
  {
    LOG(ERROR) << "can not divide non integer types";
  }

  std::cout << "# ";
  emitSource("");
  std::cout << '\n';

  RegisterPool::Register result;
  auto r_lhs = lhs->emit();
  auto r_rhs = rhs->emit();
  std::cout << "div " << r_lhs << ", " << r_rhs << '\n';
  std::cout << "mfhi " << result << " # ";

  emitSource("");
  std::cout << '\n';

  return result;
}
