#include "SimpleTypeNode.hpp"

#include <iostream>

SimpleTypeNode::SimpleTypeNode(std::string ident)
  : TypeNode(ident)
{}

void SimpleTypeNode::emitSource(std::string indent)
{
  std::cout << indent << ident;
}

RegisterPool::Register SimpleTypeNode::emit()
{
  throw "not implemented";
}
