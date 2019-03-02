#ifndef STRING_CONSTANT_NODE_HPP
#define STRING_CONSTANT_NODE_HPP

#include "ExpressionNode.hpp"

#include <string>

class StringLiteralNode : public ExpressionNode
{
public:
  StringLiteralNode(std::string);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;
  const std::string string;
};

#endif
