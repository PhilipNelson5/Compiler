#ifndef REPEAT_STATEMENT_NODE_HPP
#define REPEAT_STATEMENT_NODE_HPP

#include "ExpressionNode.hpp"
#include "ListNode.hpp"
#include "StatementNode.hpp"
#include "Value.hpp"

#include <memory>
#include <vector>

class RepeatStatementNode : public StatementNode
{
public:
  RepeatStatementNode(ListNode<StatementNode>*& statements, ExpressionNode*& expr);

  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

  std::vector<std::shared_ptr<StatementNode>> statements;
  std::shared_ptr<ExpressionNode> expr;
};

#endif
