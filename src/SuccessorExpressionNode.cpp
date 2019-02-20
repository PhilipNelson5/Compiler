#include "SuccessorExpressionNode.hpp"

#include <iostream>

SuccessorExpressionNode::SuccessorExpressionNode(ExpressionNode*& expr)
  : expr(expr)
{}

void SuccessorExpressionNode::emitSource(std::string indent)
{
  std::cout << indent << "pred(";
  expr->emitSource("");
  std::cout << ")";
}

RegisterPool::Register SuccessorExpressionNode::emit()
{
  throw "not implemented";
}
