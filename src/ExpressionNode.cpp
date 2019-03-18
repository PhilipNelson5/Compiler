#include "ExpressionNode.hpp"
class Type;

ExpressionNode::ExpressionNode(std::shared_ptr<Type> type)
  : type(type)
{}

bool ExpressionNode::isLiteral()
{
  return false;
}

bool ExpressionNode::isConstant()
{
  return false;
}
