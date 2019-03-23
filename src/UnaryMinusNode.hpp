#ifndef UNARY_MINUS_NODE_HPP
#define UNARY_MINUS_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <memory>

class UnaryMinusNode : public ExpressionNode
{
public:
  UnaryMinusNode(ExpressionNode*& right);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  const std::shared_ptr<ExpressionNode> rhs;
};

#endif
