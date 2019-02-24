#ifndef CHARACTER_EXPRESSION_NODE_HPP
#define CHARACTER_EXPRESSION_NODE_HPP

#include "ExpressionNode.hpp"

class CharacterExpressionNode : public ExpressionNode
{
public:
  CharacterExpressionNode(ExpressionNode*& expr);
  void emitSource(std::string indent) override;
  RegisterPool::Register emit() override;

private:
  std::shared_ptr<ExpressionNode> expr;
};

#endif