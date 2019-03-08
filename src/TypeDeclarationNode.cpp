#include "TypeDeclarationNode.hpp"

#include "SymbolTable.hpp"
#include "Type.hpp"

#include <iostream>

TypeDeclarationNode::TypeDeclarationNode(std::string id,
                                         std::shared_ptr<Type>* type)
  : m_id(id)
  , m_type(*type)
{
  symbol_table.storeType(m_id, m_type);
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
