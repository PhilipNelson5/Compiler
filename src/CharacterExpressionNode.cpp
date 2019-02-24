#include "CharacterExpressionNode.hpp"

#include <iostream>

CharacterExpressionNode::CharacterExpressionNode(ExpressionNode*& expr)
  : expr(expr)
{}

void CharacterExpressionNode::emitSource(std::string indent)
{
  std::cout << indent << "chr(";
  expr->emitSource("");
  std::cout << ")";
}

RegisterPool::Register CharacterExpressionNode::emit()
{
  throw "not implemented CharacterConstantNode";
}
