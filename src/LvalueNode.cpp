#include "LvalueNode.hpp"

#include <iostream>

LvalueNode::LvalueNode(std::string ident)
  : ident(ident)
{}

void LvalueNode::emitSource(std::string indent)
{
  std::cout << indent << ident;
}

RegisterPool::Register LvalueNode::emit()
{
  throw "not implemented";
}

