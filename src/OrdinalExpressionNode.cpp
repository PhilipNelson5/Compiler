#include "OrdinalExpressionNode.hpp"

#include "log/easylogging++.h"

#include <iostream>

OrdinalExpressionNode::OrdinalExpressionNode(ExpressionNode*& expr)
  : ExpressionNode(IntegerType::get())
  , expr(expr)
{}

void OrdinalExpressionNode::emitSource(std::string indent)
{
  std::cout << indent << "ord(";
  expr->emitSource("");
  std::cout << ")";
}

RegisterPool::Register OrdinalExpressionNode::emit()
{
  if (expr->type != CharacterType::get())
  {
    LOG(ERROR) << "ord is not defined on " << expr->type->name()
               << ". Must use character type";
    exit(EXIT_FAILURE);
  }

  expr->type = IntegerType::get();

  return expr->emit();
}
