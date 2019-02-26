#include "BooleanConstantNode.hpp"

#include "RegisterPool.hpp"
#include "Type.hpp"

#include <iostream>
#include <iomanip>

BooleanConstantNode::BooleanConstantNode(int value)
  : value(value)
{}

std::shared_ptr<Type> BooleanConstantNode::type()
{
  return IntegerType::get();
}

void BooleanConstantNode::emitSource(std::string indent)
{
  std::cout << indent << std::boolalpha << value;
}

RegisterPool::Register BooleanConstantNode::emit()
{
  RegisterPool::Register reg;
  std::cout <<  "li " << reg << ", " << value << " # load ";
  emitSource("");
  std::cout << std::endl;

  return reg;
}
