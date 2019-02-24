#ifndef ADD_NODE_HPP
#define ADD_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <memory>

class AddNode : public ExpressionNode
{
public:
  AddNode(ExpressionNode*& left, ExpressionNode*& right);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;

private:
  std::shared_ptr<ExpressionNode> lhs;
  std::shared_ptr<ExpressionNode> rhs;
};

#endif
