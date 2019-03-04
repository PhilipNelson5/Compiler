#include "SuccessorExpressionNode.hpp"

#include <iostream>

SuccessorExpressionNode::SuccessorExpressionNode(ExpressionNode*& expr)
  : ExpressionNode(expr->type)
  , expr(expr)
{}

void SuccessorExpressionNode::emitSource(std::string indent)
{
  std::cout << indent << "pred(";
  expr->emitSource("");
  std::cout << ")";
}

Value SuccessorExpressionNode::emit()
{
  throw "not implemented SuccessorExpressionNode";
}
