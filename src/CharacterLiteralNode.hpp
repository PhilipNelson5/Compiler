#ifndef CHARACTER_CONSTANT_NODE_HPP
#define CHARACTER_CONSTANT_NODE_HPP

#include "LiteralNode.hpp" // for LiteralNode
#include "Value.hpp"       // for Value

#include <string> // for string

class CharacterLiteralNode : public LiteralNode
{
public:
  CharacterLiteralNode(char character);
  virtual bool isLiteral() override;
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;
  std::string toString() const;
  const char character;
};

#endif
