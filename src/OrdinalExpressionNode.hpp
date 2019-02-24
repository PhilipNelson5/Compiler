#ifndef ORDINAL_EXPRESSION_NODE_HPP
#define ORDINAL_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class OrdinalExpressionNode : public ExpressionNode
{
public:
  OrdinalExpressionNode(ExpressionNode*& expr);
  void emitSource(std::string indent) override;
  RegisterPool::Register emit() override;

private:
  std::shared_ptr<ExpressionNode> expr;
};

#endif
