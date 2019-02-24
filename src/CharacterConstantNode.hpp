#ifndef CHARACTER_CONSTANT_NODE_HPP
#define CHARACTER_CONSTANT_NODE_HPP

#include "ExpressionNode.hpp"

class CharacterConstantNode : public ExpressionNode
{
public:
  CharacterConstantNode(char character);
  virtual std::shared_ptr<Type> type() override;
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;

private:
  char character;
};

#endif
