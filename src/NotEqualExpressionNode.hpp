#ifndef NOT_EQUAL_EXPRESSION_NODE_HPP
#define NOT_EQUAL_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class NotEqualExpressionNode : public ExpressionNode
{
public:
  NotEqualExpressionNode(ExpressionNode*& lhs, ExpressionNode*& rhs);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::shared_ptr<ExpressionNode> lhs;
  std::shared_ptr<ExpressionNode> rhs;
};

#endif
