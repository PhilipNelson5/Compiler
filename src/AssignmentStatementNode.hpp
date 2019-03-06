#ifndef ASSIGNEMNT_STATEMENT_NODE_HPP
#define ASSIGNEMNT_STATEMENT_NODE_HPP

#include "ExpressionNode.hpp"
#include "LvalueNode.hpp"
#include "RegisterPool.hpp"
#include "StatementNode.hpp"

#include <memory>

class AssignmentStatementNode : public StatementNode
{
public:
  AssignmentStatementNode(LvalueNode*& lval, ExpressionNode* expr);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::shared_ptr<LvalueNode> lval;
  std::shared_ptr<ExpressionNode> expr;
};

#endif
