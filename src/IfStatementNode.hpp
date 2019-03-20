#ifndef IF_STATEMENT_NODE_HPP
#define IF_STATEMENT_NODE_HPP

#include "ListNode.hpp"
#include "StatementNode.hpp"

#include <memory>
#include <utility>
#include <vector>
class ExpressionNode;
class ThenBodyNode;
class ElseIfStatementNode;
class ElseStatementNode;

using IfStatement
  = std::pair<std::shared_ptr<ExpressionNode>, std::vector<std::shared_ptr<StatementNode>>>;

class IfStatementNode : public StatementNode
{
public:
  IfStatementNode(ExpressionNode*& ifExpr, ListNode<StatementNode>*& ifStatements);
  virtual void emitSource(std::string indent) override;
  virtual ~IfStatementNode() override = default;
  virtual Value emit() override;

  const IfStatement ifStatement;
  const std::vector<IfStatement> elseIfStatements;
  const std::vector<std::shared_ptr<StatementNode>> elseStatement;
};

#endif
