#include "AssignmentStatementNode.hpp"

#include <iostream>

AssignmentStatementNode::AssignmentStatementNode(LvalueNode*& lval,
                                                 ExpressionNode* expr)
  : lval(std::shared_ptr<LvalueNode>(lval))
  , expr(std::shared_ptr<ExpressionNode>(expr))
{}

void AssignmentStatementNode::emitSource(std::string indent)
{
  std::cout << indent;
  lval->emitSource("");
  std::cout << " := ";
  expr->emitSource("");
  std::cout << ";" << std::endl;
}

RegisterPool::Register AssignmentStatementNode::emit()
{
  throw "not implemented";
}
