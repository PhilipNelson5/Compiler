#ifndef OR_NODE_HPP
#define OR_NODE_HPP

#include "ExpressionNode.hpp" // for ExpressionNode
#include "Value.hpp"          // for Value

#include <memory> // for shared_ptr
#include <string> // for string

class OrNode : public ExpressionNode
{
public:
  OrNode(ExpressionNode*& left, ExpressionNode*& right);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  const std::shared_ptr<ExpressionNode> lhs;
  const std::shared_ptr<ExpressionNode> rhs;
};

#endif
