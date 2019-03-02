#include "ExpressionNode.hpp"

#include "SymbolTable.hpp"
#include "log/easylogging++.h"

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
