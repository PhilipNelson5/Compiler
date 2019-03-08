#include "VariableDeclarationNode.hpp"

#include "SymbolTable.hpp"

#include <iostream>
#include <string.h>
#include <string>

VariableDeclarationNode::VariableDeclarationNode(
  ListNode<std::string>* identList,
  std::shared_ptr<Type>* type)
  : m_ids(ListNode<std::string>::makeDerefVector(identList))
  , m_type(*type)
{
  for (auto&& id : m_ids)
    symbol_table.storeVariable(id, m_type);
}

void VariableDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent;
  for (auto i = 0u; i < m_ids.size() - 1; ++i)
  {
    std::cout << m_ids[i] << ", ";
  }
  std::cout << m_ids.back() << " : ";
  m_type->emitSource("");
  std::cout << ";" << std::endl;
}

Value VariableDeclarationNode::emit()
{
  throw "VariableDeclarationNode::emit() should not be called";
}
