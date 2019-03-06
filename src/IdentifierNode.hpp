#ifndef IDENTIFIER_NODE_HPP
#define IDENTIFIER_NODE_HPP

#include "LvalueNode.hpp"

#include <string>

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
