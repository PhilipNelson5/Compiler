#include "AddNode.hpp"

AddNode::AddNode(ExpressionNode*& left, ExpressionNode*& right)
  : left(std::shared_ptr<ExpressionNode>(left))
  , right(std::shared_ptr<ExpressionNode>(right))
{
}

void AddNode::emmitSource()
{
  throw "not implemented";
}

RegisterPool::Register AddNode::emmit()
{
  throw "not implemented";
}
