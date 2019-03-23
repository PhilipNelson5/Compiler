#ifndef SUCCESSOR_EXPRESSION_NODE_HPP
#define SUCCESSOR_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class SuccessorExpressionNode : public ExpressionNode
{
public:
  SuccessorExpressionNode(ExpressionNode*& expr);
  virtual const std::shared_ptr<Type> getType() override;
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  const std::shared_ptr<ExpressionNode> expr;
};

#endif
