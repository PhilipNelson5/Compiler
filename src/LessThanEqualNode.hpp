#ifndef LESS_THAN_EQUAL_NODE_HPP
#define LESS_THAN_EQUAL_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <memory>

class LessThanEqualNode : public ExpressionNode
{
public:
  LessThanEqualNode(ExpressionNode*& left, ExpressionNode*& right);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  const std::shared_ptr<ExpressionNode> lhs;
  const std::shared_ptr<ExpressionNode> rhs;
};

#endif
