#include "LvalueNode.hpp"

#include "SymbolTable.hpp"

#include <iostream>

LvalueNode::LvalueNode(std::string ident)
  : ident(ident)
{}

void LvalueNode::emitSource(std::string indent)
{
  std::cout << indent << ident;
}

RegisterPool::Register LvalueNode::emit()
{
  auto loc = symbol_table.lookupVariable(ident);
  RegisterPool::Register reg;
  std::cout << "lw " << reg << ", " << loc.getLoc() << " # ";
  emitSource("");
  std::cout << std::endl;
  return reg;
}
