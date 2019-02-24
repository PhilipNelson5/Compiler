#ifndef LVALUE_NODE_HPP
#define LVALUE_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <string>

class LvalueNode : public ExpressionNode
{
public:
  LvalueNode(std::string ident);
  std::shared_ptr<Type> type() override;
  void emitSource(std::string indent) override;
  RegisterPool::Register emit() override;

  std::string ident;
};

#endif
