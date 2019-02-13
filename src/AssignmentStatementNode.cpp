#include "AssignmentStatementNode.hpp"

#include <iostream>

AssignmentStatementNode::AssignmentStatementNode(LvalueNode*& lval,
                                                 ExpressionNode* expr)
  : lval(std::shared_ptr<LvalueNode>(lval))
  , expr(std::shared_ptr<ExpressionNode>(expr))
{}

void AssignmentStatementNode::emmitSource(std::string indent)
{
  std::cout << indent;
  lval->emmitSource("");
  std::cout << " := ";
  expr->emmitSource("");
  std::cout << ";" << std::endl;
}

RegisterPool::Register AssignmentStatementNode::emmit()
{
  throw "not implemented";
}
