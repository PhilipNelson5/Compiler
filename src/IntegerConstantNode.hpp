#ifndef INTEGER_CONSTANT_NODE_HPP
#define INTEGER_CONSTANT_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

class IntegerConstantNode : public ExpressionNode
{
  public:
  IntegerConstantNode(int value);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;

private:
  int value;
};

#endif
