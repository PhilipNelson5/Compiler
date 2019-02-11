#ifndef LVALUE_NODE_HPP
#define LVALUE_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <string>

class LvalueNode : public ExpressionNode
{
public:
  LvalueNode(std::string ident);
  void emmitSource() override;
  RegisterPool::Register emmit() override;
  std::string ident;
};

#endif
