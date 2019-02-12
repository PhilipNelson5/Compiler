#include "LvalueNode.hpp"

#include <iostream>

LvalueNode::LvalueNode(std::string ident)
  : ident(ident)
{}

void LvalueNode::emmitSource()
{
  std::cout << "Lvalue Node" << std::endl;
}

RegisterPool::Register LvalueNode::emmit()
{
  throw "not implemented";
}

