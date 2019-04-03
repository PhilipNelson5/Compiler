#ifndef RETURN_STATMENT_NODE_HPP
#define RETURN_STATMENT_NODE_HPP

#include "ExpressionNode.hpp"
#include "StatementNode.hpp"
#include "Value.hpp"

#include <memory>

class ReturnStatementNode : public StatementNode
{
public:
  ReturnStatementNode()
    : expr(nullptr)
  {}

  ReturnStatementNode(ExpressionNode*& expr)
    : expr(expr)
  {}

  virtual void emitSource(std::string indent) override;
  virtual void emit() override;

  const std::shared_ptr<ExpressionNode> expr;
};

#endif
