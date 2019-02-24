#include "TypeDeclarationNode.hpp"

#include <iostream>

TypeDeclarationNode::TypeDeclarationNode(std::string ident, TypeNode* type)
  : ident(ident)
  , type(type)
{}

void TypeDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent << ident << " = ";
  type->emitSource("");
  std::cout << ";" << std::endl;
}

RegisterPool::Register TypeDeclarationNode::emit()
{
  return {};
}
