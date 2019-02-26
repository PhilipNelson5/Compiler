#include "IntegerConstantNode.hpp"

#include "RegisterPool.hpp"
#include "Type.hpp"

#include <iostream>

IntegerConstantNode::IntegerConstantNode(int value)
  : value(value)
{}

std::shared_ptr<Type> IntegerConstantNode::type()
{
  return IntegerType::get();
}

bool IntegerConstantNode::isLiteral()
{
  return true;
}

void IntegerConstantNode::emitSource(std::string indent)
{
  std::cout << indent << value;
}

RegisterPool::Register IntegerConstantNode::emit()
{
  RegisterPool::Register reg;
  std::cout << "li " << reg << ", " << value << " # load ";
  emitSource("");
  std::cout << std::endl;

  return reg;
}
