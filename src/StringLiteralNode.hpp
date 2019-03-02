#ifndef STRING_CONSTANT_NODE_HPP
#define STRING_CONSTANT_NODE_HPP

#include "LiteralNode.hpp"
#include "RegisterPool.hpp"

#include <string>

class StringLiteralNode : public LiteralNode
{
public:
  StringLiteralNode(std::string);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;
  const std::string string;
};

#endif
