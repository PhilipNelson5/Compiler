#ifndef LVALUE_NODE_HPP
#define LVALUE_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <string>

class LvalueNode : public ExpressionNode
{
public:
  LvalueNode(std::string ident);
  virtual bool isConstant() override;
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

  const std::string id;
};

#endif
