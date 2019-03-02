#ifndef BOOLEAN_CONSTANT_NODE_HPP
#define BOOLEAN_CONSTANT_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

class BooleanLiteralNode : public ExpressionNode
{
public:
  BooleanLiteralNode(int value);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;
  const bool value;
};

#endif
