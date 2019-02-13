#include "LvalueNode.hpp"

#include <iostream>

LvalueNode::LvalueNode(std::string ident)
  : ident(ident)
{}

void LvalueNode::emmitSource(std::string indent)
{
  std::cout << indent << ident;
}

RegisterPool::Register LvalueNode::emmit()
{
  throw "not implemented";
}

