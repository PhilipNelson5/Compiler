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
  std::cout << indent << std::boolalpha << value << std::noboolalpha;
}

Value BooleanLiteralNode::emit()
{
  return {value};
}
