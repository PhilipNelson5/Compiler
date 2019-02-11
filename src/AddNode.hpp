#ifndef ADD_NODE_HPP
#define ADD_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <memory>

class AddNode : public ExpressionNode
{
public:
  AddNode(ExpressionNode*& left, ExpressionNode*& right);
  virtual void emmitSource() override;
  virtual RegisterPool::Register emmit() override;

private:
  std::shared_ptr<ExpressionNode> left;
  std::shared_ptr<ExpressionNode> right;
};

#endif
