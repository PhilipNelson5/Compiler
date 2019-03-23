#ifndef PREDECESSOR_EXPRESSION_NODE_HPP
#define PREDECESSOR_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp" // for ExpressionNode
#include "Value.hpp"          // for Value

#include <memory> // for shared_ptr
#include <string> // for string

class PredecessorExpressionNode : public ExpressionNode
{
public:
  PredecessorExpressionNode(ExpressionNode*& expr);
  virtual const std::shared_ptr<Type> getType() override;
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  const std::shared_ptr<ExpressionNode> expr;
};

#endif
