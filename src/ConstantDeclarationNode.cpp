#include "ConstantDeclarationNode.hpp"

#include "SymbolTable.hpp"

#include <iostream>

ConstantDeclarationNode::ConstantDeclarationNode(std::string id,
                                                 ExpressionNode* expr)
  : m_id(id)
  , m_expr(dynamic_cast<LiteralNode*>(expr))
{
  symbol_table.storeConst(m_id, m_expr);
}

void ConstantDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent << m_id << " = ";
  m_expr->emitSource("");
  std::cout << ";" << std::endl;
}

RegisterPool::Register ConstantDeclarationNode::emit()
{
  throw "ConstantDeclarationNode::emit() should not be called";
}
