#include "TypeDeclarationNode.hpp"

#include "SymbolTable.hpp"

#include <iostream>

TypeDeclarationNode::TypeDeclarationNode(std::string id, TypeNode* type)
  : m_id(id)
  , m_type(type)
{
  //TODO: check for other types of types
  auto typeType = symbol_table.lookupType(m_type->ident);
  symbol_table.storeType(m_id, typeType);
}

void TypeDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent << m_id << " = ";
  m_type->emitSource("");
  std::cout << ";" << std::endl;
}

Value TypeDeclarationNode::emit()
{
  throw "TypeDeclarationNode::emit() should not be called";
}
