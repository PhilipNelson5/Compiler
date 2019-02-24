#ifndef STRING_CONSTANT_NODE_HPP
#define STRING_CONSTANT_NODE_HPP

#include "ExpressionNode.hpp"

#include <string>

class StringConstantNode : public ExpressionNode
{
public:
  StringConstantNode(std::string);
  virtual std::shared_ptr<Type> type() override;
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;

private:
  std::string string;
};

#endif
