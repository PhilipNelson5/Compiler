#ifndef CHARACTER_EXPRESSION_NODE_HPP
#define CHARACTER_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp" // for ExpressionNode
#include "Value.hpp"          // for Value

#include <memory> // for shared_ptr
#include <string> // for string

class CharacterExpressionNode : public ExpressionNode
{
public:
  CharacterExpressionNode(ExpressionNode*& expr);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::shared_ptr<ExpressionNode> expr;
};

#endif
