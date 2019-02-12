#include "AssignmentStatementNode.hpp"

#include <iostream>

AssignmentStatementNode::AssignmentStatementNode(LvalueNode*& lval,
                                                 ExpressionNode* expr)
  : lval(std::shared_ptr<LvalueNode>(lval))
  , expr(std::shared_ptr<ExpressionNode>(expr))
{}

void AssignmentStatementNode::emmitSource()
{
  std::cout << "Assignment Statement Node" << std::endl;
}

RegisterPool::Register AssignmentStatementNode::emmit()
{
  throw "not implemented";
}
