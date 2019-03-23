#include "TypeDeclarationNode.hpp"

#include "SymbolTable.hpp"
#include "Type.hpp"

#include <iostream>

TypeDeclarationNode::TypeDeclarationNode(std::string id, TypeNode*& typeNode)
  : m_id(id)
  , m_type(typeNode->type)
{
  // TODO move to the emit function;
  symbol_table.storeType(m_id, m_type);
}

void TypeDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent << m_id << " = ";
  m_type->emitSource(indent + "  ");
  std::cout << ";" << std::endl;
}

void TypeDeclarationNode::emit()
{
  throw "TypeDeclarationNode::emit() should not be called";
}
