#ifndef CHARACTER_CONSTANT_NODE_HPP
#define CHARACTER_CONSTANT_NODE_HPP

#include "ExpressionNode.hpp"

class CharacterLiteralNode : public ExpressionNode
{
public:
  CharacterLiteralNode(char character);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;
  const char character;
};

#endif
