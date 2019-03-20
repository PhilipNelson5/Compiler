#ifndef FOR_STATEMENT_NODE_HPP
#define FOR_STATEMENT_NODE_HPP

#include "ExpressionNode.hpp"
#include "ListNode.hpp"
#include "StatementNode.hpp"

#include <memory>
#include <vector>

class ForStatementNode : public StatementNode
{
public:
  enum Type
  {
    TO,
    DOWNTO
  };

  ForStatementNode(char*& id,
                   ExpressionNode*& startExpr,
                   ExpressionNode*& endExpr,
                   ListNode<StatementNode>*& statements,
                   Type type);

  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

  std::string id;
  std::shared_ptr<ExpressionNode> startExpr;
  std::shared_ptr<ExpressionNode> endExpr;
  std::vector<std::shared_ptr<StatementNode>> statements;
  Type type;
};

#endif
