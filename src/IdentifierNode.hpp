#ifndef IDENTIFIER_NODE_HPP
#define IDENTIFIER_NODE_HPP

#include "LvalueNode.hpp" // for LvalueNode
#include "Value.hpp"      // for Value

#include <string> // for string

class IdentifierNode : public LvalueNode
{
public:
  IdentifierNode(std::string id);
  virtual bool isConstant() override;
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

  virtual std::string getId() override;

  const std::string id;
};

#endif
