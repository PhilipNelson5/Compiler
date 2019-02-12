#include "IntegerConstantNode.hpp"

#include <iostream>

IntegerConstantNode::IntegerConstantNode(int value)
  : value(value)
{}

void IntegerConstantNode::emmitSource()
{
  std::cout << "Integer Constant Node" << std::endl;
}

RegisterPool::Register IntegerConstantNode::emmit()
{
  throw "not implemented";
}
