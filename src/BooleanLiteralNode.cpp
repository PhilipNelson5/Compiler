#include "BooleanLiteralNode.hpp"

#include "RegisterPool.hpp"
#include "Type.hpp"

#include <iomanip>
#include <iostream>

BooleanLiteralNode::BooleanLiteralNode(int value)
  : LiteralNode(BooleanType::get())
  , value(value)
{}

void BooleanLiteralNode::emitSource(std::string indent)
{
  std::cout << indent << std::boolalpha << value;
}

RegisterPool::Register BooleanLiteralNode::emit()
{
  RegisterPool::Register reg;
  std::cout << "li " << reg << ", " << value << " # load ";
  emitSource("");
  std::cout << std::endl;

  return reg;
}
