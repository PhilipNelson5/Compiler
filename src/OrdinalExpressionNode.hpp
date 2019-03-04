#ifndef ORDINAL_EXPRESSION_NODE_HPP
#define ORDINAL_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class OrdinalExpressionNode : public ExpressionNode
{
public:
  OrdinalExpressionNode(ExpressionNode*& expr);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::shared_ptr<ExpressionNode> expr;
};

#endif
