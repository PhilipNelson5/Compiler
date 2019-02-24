#ifndef SUCCESSOR_EXPRESSION_NODE_HPP
#define SUCCESSOR_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class SuccessorExpressionNode : public ExpressionNode
{
public:
  SuccessorExpressionNode(ExpressionNode*& expr);
  void emitSource(std::string indent) override;
  RegisterPool::Register emit() override;

private:
  std::shared_ptr<ExpressionNode> expr;
};

#endif
