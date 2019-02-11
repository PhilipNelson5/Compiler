#include "LvalueNode.hpp"

LvalueNode::LvalueNode(std::string ident)
  : ident(ident)
{}

void LvalueNode::emmitSource() {}

RegisterPool::Register LvalueNode::emmit()
{
  throw "not implemented";
}

