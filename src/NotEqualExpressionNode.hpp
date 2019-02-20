#ifndef NOT_EQUAL_EXPRESSION_NODE_HPP
#define NOT_EQUAL_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class NotEqualExpressionNode : public ExpressionNode
{
public:
  NotEqualExpressionNode(ExpressionNode*& lhs, ExpressionNode*& rhs);
  void emitSource(std::string indent) override;
  RegisterPool::Register emit() override;

private:
  std::shared_ptr<ExpressionNode> lhs;
  std::shared_ptr<ExpressionNode> rhs;
};

#endif
