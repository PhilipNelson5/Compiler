#include "OrdinalExpressionNode.hpp"

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
  throw "not implemented OrdinalExpressionNode";
}
