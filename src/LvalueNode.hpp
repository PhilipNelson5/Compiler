#ifndef LVALUE_NODE_HPP
#define LVALUE_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <string>

class LvalueNode : public ExpressionNode
{
public:
  LvalueNode(std::string ident);
  bool isConstant() override;
  void emitSource(std::string indent) override;
  RegisterPool::Register emit() override;

  const std::string ident;
};

#endif
