#include "TypeDeclarationNode.hpp"

#include "SymbolTable.hpp"
#include "Type.hpp"

#include <iostream>

TypeDeclarationNode::TypeDeclarationNode(std::string id, TypeNode*& typeNode)
  : m_id(id)
  , m_type(typeNode->type)
{
  symbol_table.storeType(m_id, m_type);
}

void TypeDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent << m_id << " = ";
  m_type->emitSource(indent + "  ");
  std::cout << ";" << std::endl;
}

Value TypeDeclarationNode::emit()
{
  throw "TypeDeclarationNode::emit() should not be called";
}
