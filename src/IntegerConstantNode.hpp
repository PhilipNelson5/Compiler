#ifndef INTEGER_CONSTANT_NODE_HPP
#define INTEGER_CONSTANT_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

class IntegerConstantNode : public ExpressionNode
{
  public:
  IntegerConstantNode(int value);
  virtual bool isLiteral() override;
  virtual std::shared_ptr<Type> type() override;
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;
  int value;
};

#endif
