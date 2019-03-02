#include "PredecessorExpressionNode.hpp"

#include <iostream>

PredecessorExpressionNode::PredecessorExpressionNode(ExpressionNode*& expr)
  : ExpressionNode(expr->type)
  , expr(expr)
{}

void PredecessorExpressionNode::emitSource(std::string indent)
{
  std::cout << indent << "pred(";
  expr->emitSource("");
  std::cout << ")";
}

RegisterPool::Register PredecessorExpressionNode::emit()
{
  throw "not implemented PredecessorExpressionNode";
}
