#ifndef OR_NODE_HPP
#define OR_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <memory>

class OrNode : public ExpressionNode
{
public:
  OrNode(ExpressionNode*& left, ExpressionNode*& right);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::shared_ptr<ExpressionNode> lhs;
  std::shared_ptr<ExpressionNode> rhs;
};

#endif
