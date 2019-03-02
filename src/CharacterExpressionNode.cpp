#include "CharacterExpressionNode.hpp"

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
  throw "not implemented CharacterLiteralNode";
}
