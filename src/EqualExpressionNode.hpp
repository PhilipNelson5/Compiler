#ifndef EQUAL_EXPRESSION_NODE_HPP
#define EQUAL_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class EqualExpressionNode : public ExpressionNode
{
public:
  EqualExpressionNode(ExpressionNode*& lhs, ExpressionNode*& rhs);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;

private:
  std::shared_ptr<ExpressionNode> lhs;
  std::shared_ptr<ExpressionNode> rhs;
};


#endif
