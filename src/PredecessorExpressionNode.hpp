#ifndef PREDECESSOR_EXPRESSION_NODE_HPP
#define PREDECESSOR_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class PredecessorExpressionNode : public ExpressionNode
{
public:
  PredecessorExpressionNode(ExpressionNode*& expr);
  void emitSource(std::string indent) override;
  RegisterPool::Register emit() override;

private:
  std::shared_ptr<ExpressionNode> expr;
};

#endif
