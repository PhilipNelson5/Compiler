#ifndef NOT_NODE_HPP
#define NOT_NODE_HPP

#include "ExpressionNode.hpp" // for ExpressionNode
#include "Value.hpp"          // for Value

#include <memory> // for shared_ptr
#include <string> // for string

class NotNode : public ExpressionNode
{
public:
  NotNode(ExpressionNode*& right);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  const std::shared_ptr<ExpressionNode> rhs;
};

#endif
