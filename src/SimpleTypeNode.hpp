#ifndef SIMPLE_TYPE_NODE_HPP
#define SIMPLE_TYPE_NODE_HPP

#include "TypeNode.hpp"

class SimpleTypeNode : public TypeNode
{
public:
  SimpleTypeNode(std::string ident);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;
};

#endif
