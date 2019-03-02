#include "ConstantDeclarationNode.hpp"

#include "SymbolTable.hpp"

#include <iostream>

ConstantDeclarationNode::ConstantDeclarationNode(std::string ident,
                                                 ExpressionNode* expr)
  : ident(ident)
  , expr(expr)
{}

void ConstantDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent << ident << " = ";
  expr->emitSource("");
  std::cout << ";" << std::endl;
}

RegisterPool::Register ConstantDeclarationNode::emit()
{
  symbol_table.storeConst(ident, expr);
  return {};
}
