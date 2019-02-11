#include "AssignmentStatementNode.hpp"

AssignmentStatementNode::AssignmentStatementNode(LvalueNode*& lval,
                                                 ExpressionNode* expr)
  : lval(std::shared_ptr<LvalueNode>(lval))
  , expr(std::shared_ptr<ExpressionNode>(expr))
{}

void AssignmentStatementNode::emmitSource()
{
  throw "not implemented";
}

RegisterPool::Register AssignmentStatementNode::emmit()
{
  throw "not implemented";
}
