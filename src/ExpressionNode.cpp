#include "ExpressionNode.hpp"

ExpressionNode::ExpressionNode()
  : type(IntegerType::get())
{}

ExpressionNode::ExpressionNode(std::shared_ptr<Type> type)
  : type(type)
{}

bool ExpressionNode::isLiteral()
{
  return false;
}
