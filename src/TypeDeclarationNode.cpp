#include "TypeDeclarationNode.hpp"

#include "SymbolTable.hpp"

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
  //TODO: check for other types of types
  auto typeType = symbol_table.lookupType(type->ident);
  symbol_table.storeType(ident, typeType);
  return {};
}
