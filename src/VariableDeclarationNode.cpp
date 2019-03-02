#include "VariableDeclarationNode.hpp"

#include "SymbolTable.hpp"

#include <iostream>
#include <string.h>
#include <string>

VariableDeclarationNode::VariableDeclarationNode(
  ListNode<std::string>* identList,
  TypeNode* type)
  : m_ids(ListNode<std::string>::makeDerefVector(identList))
  , m_type(type)
{
  auto pType = symbol_table.lookupType(m_type->ident);
  for (auto&& id : m_ids)
    symbol_table.storeVariable(id, pType);
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

RegisterPool::Register VariableDeclarationNode::emit()
{
  throw "VariableDeclarationNode::emit() should not be called";
}
