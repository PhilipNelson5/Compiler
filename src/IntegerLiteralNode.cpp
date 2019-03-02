#include "IntegerLiteralNode.hpp"

#include "RegisterPool.hpp"
#include "Type.hpp"

#include <iostream>

IntegerLiteralNode::IntegerLiteralNode(int value)
  : LiteralNode(IntegerType::get())
  , value(value)
{}

bool IntegerLiteralNode::isLiteral()
{
  return true;
}

void IntegerLiteralNode::emitSource(std::string indent)
{
  std::cout << indent << value;
}

RegisterPool::Register IntegerLiteralNode::emit()
{
  RegisterPool::Register reg;
  std::cout << "li " << reg << ", " << value << " # load ";
  emitSource("");
  std::cout << std::endl;

  return reg;
}
