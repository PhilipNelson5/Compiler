#include "CharacterExpressionNode.hpp"
#include "log/easylogging++.h"

#include <iostream>

CharacterExpressionNode::CharacterExpressionNode(ExpressionNode*& expr)
  : ExpressionNode(CharacterType::get())
  , expr(expr)
{}

void CharacterExpressionNode::emitSource(std::string indent)
{
  std::cout << indent << "chr(";
  expr->emitSource("");
  std::cout << ")";
}

RegisterPool::Register CharacterExpressionNode::emit()
{
  if (expr->type != IntegerType::get())
  {
    LOG(ERROR) << "chr is not defined on " << expr->type->name()
               << ". Must use integer type";
    exit(EXIT_FAILURE);
  }

  expr->type = CharacterType::get();

  return expr->emit();
}
