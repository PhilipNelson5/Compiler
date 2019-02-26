#ifndef BOOLEAN_CONSTANT_NODE_HPP
#define BOOLEAN_CONSTANT_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

class BooleanConstantNode : public ExpressionNode
{
  public:
  BooleanConstantNode(int value);
  virtual std::shared_ptr<Type> type() override;
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;

private:
  bool value;
};

#endif
