#ifndef EQUAL_EXPRESSION_NODE_HPP
#define EQUAL_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp" // for ExpressionNode
#include "Value.hpp"          // for Value

#include <memory> // for shared_ptr
#include <string> // for string

class EqualExpressionNode : public ExpressionNode
{
public:
  EqualExpressionNode(ExpressionNode*& lhs, ExpressionNode*& rhs);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::shared_ptr<ExpressionNode> lhs;
  std::shared_ptr<ExpressionNode> rhs;
};


#endif
