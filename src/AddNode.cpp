#include "AddNode.hpp"

#include <iostream>

AddNode::AddNode(ExpressionNode*& left, ExpressionNode*& right)
  : left(std::shared_ptr<ExpressionNode>(left))
  , right(std::shared_ptr<ExpressionNode>(right))
{}

void AddNode::emitSource(std::string indent)
{
  std::cout << indent << "Add Node" << std::endl;
}

RegisterPool::Register AddNode::emit()
{
  throw "not implemented";
}
