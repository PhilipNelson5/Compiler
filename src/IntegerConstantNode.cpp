#include "IntegerConstantNode.hpp"
#include "RegisterPool.hpp"
#include "Type.hpp"

#include <iostream>

IntegerConstantNode::IntegerConstantNode(int value)
  : ExpressionNode(IntegerType::get()), value(value)
{}

void IntegerConstantNode::emitSource(std::string indent)
{
  std::cout << indent << value;
}

RegisterPool::Register IntegerConstantNode::emit()
{
  RegisterPool::Register reg;
  std::cout << "li " << reg << ", " << value << " # ";
  emitSource("");
  std::cout << std::endl;

  return reg;
}
