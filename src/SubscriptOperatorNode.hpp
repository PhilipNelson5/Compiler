#ifndef SUBSCRIPT_OPERATOR_NODE_HPP
#define SUBSCRIPT_OPERATOR_NODE_HPP

#include "LvalueNode.hpp"

class SubscriptOperatorNode : public LvalueNode
{
public:
  SubscriptOperatorNode(LvalueNode* lVal, ExpressionNode* expr);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

  std::shared_ptr<LvalueNode> lValue;
  std::shared_ptr<ExpressionNode> expr;
};

#endif
