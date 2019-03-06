#ifndef NOT_NODE_HPP
#define NOT_NODE_HPP

#include "ExpressionNode.hpp"
#include "RegisterPool.hpp"

#include <memory>

class NotNode : public ExpressionNode
{
public:
  NotNode(ExpressionNode*& right);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::shared_ptr<ExpressionNode> rhs;
};

#endif
