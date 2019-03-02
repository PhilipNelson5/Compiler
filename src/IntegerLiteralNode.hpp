#ifndef INTEGER_CONSTANT_NODE_HPP
#define INTEGER_CONSTANT_NODE_HPP

#include "LiteralNode.hpp"
#include "RegisterPool.hpp"

class IntegerLiteralNode : public LiteralNode
{
  public:
  IntegerLiteralNode(int value);
  virtual bool isLiteral() override;
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;
  const int value;
};

#endif
