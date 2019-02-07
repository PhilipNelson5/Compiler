#ifndef ADD_NODE_HPP
#define ADD_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <memory>

class AddNode : public ExpressionNode
{
public:
  void emmitSource() override;
  RegisterPool::Register emmit() override;

private:
  std::unique_ptr<ExpressionNode> left;
  std::unique_ptr<ExpressionNode> right;
};

#endif
