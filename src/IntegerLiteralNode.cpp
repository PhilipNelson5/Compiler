#include "IntegerLiteralNode.hpp"

#include "RegisterPool.hpp"
#include "Type.hpp"

#include <iostream>

IntegerLiteralNode::IntegerLiteralNode(int value)
  : LiteralNode(IntegerType::get())
  , value(value)
{}

void IntegerLiteralNode::emitSource(std::string indent)
{
  std::cout << indent << value;
}

Value IntegerLiteralNode::emit()
{
  return value;
}
