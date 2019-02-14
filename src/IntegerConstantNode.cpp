#include "IntegerConstantNode.hpp"

#include <iostream>

IntegerConstantNode::IntegerConstantNode(int value)
  : value(value)
{}

void IntegerConstantNode::emitSource(std::string indent)
{
  std::cout << indent << value;
}

RegisterPool::Register IntegerConstantNode::emit()
{
  throw "not implemented";
}
