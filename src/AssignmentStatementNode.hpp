#ifndef ASSIGNEMNT_STATEMENT_NODE_HPP
#define ASSIGNEMNT_STATEMENT_NODE_HPP

#include <memory>             // for shared_ptr
#include <string>             // for string
#include "StatementNode.hpp"  // for StatementNode
#include "LvalueNode.hpp"
#include "Value.hpp"          // for Value

class ExpressionNode;
class IdentifierNode;

class AssignmentStatementNode : public StatementNode
{
public:
  AssignmentStatementNode(LvalueNode*& lval, ExpressionNode* expr);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::shared_ptr<LvalueNode> identifier;
  std::shared_ptr<ExpressionNode> expr;
};

#endif
