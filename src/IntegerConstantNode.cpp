#include "IntegerConstantNode.hpp"

#include <iostream>

IntegerConstantNode::IntegerConstantNode(int value)
  : value(value)
{}

void IntegerConstantNode::emmitSource(std::string indent)
{
  std::cout << indent << value;
}

RegisterPool::Register IntegerConstantNode::emmit()
{
  throw "not implemented";
}
