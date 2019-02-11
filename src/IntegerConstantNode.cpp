#include "IntegerConstantNode.hpp"

IntegerConstantNode::IntegerConstantNode(int value)
  : value(value)
{}

void IntegerConstantNode::emmitSource() {}

RegisterPool::Register IntegerConstantNode::emmit()
{
  throw "not implemented";
}
