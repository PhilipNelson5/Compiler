#ifndef PREDECESSOR_EXPRESSION_NODE_HPP
#define PREDECESSOR_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class PredecessorExpressionNode : public ExpressionNode
{
public:
  PredecessorExpressionNode(ExpressionNode*& expr);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::shared_ptr<ExpressionNode> expr;
};

#endif
