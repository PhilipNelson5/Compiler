#include "StringConstantNode.hpp"

#include <iostream>

StringConstantNode::StringConstantNode(std::string string)
  : string(string)
{}

void StringConstantNode::emitSource(std::string indent)
{
  std::cout << indent << string;
}

RegisterPool::Register StringConstantNode::emit()
{
  throw "not implemented StringConstantNode StringConstantNode";
}
