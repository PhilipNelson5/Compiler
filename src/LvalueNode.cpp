#include "LvalueNode.hpp"

#include "SymbolTable.hpp"

#include <iostream>

LvalueNode::LvalueNode(std::string ident)
  : ident(ident)
{}

std::shared_ptr<Type> LvalueNode::type()
{
  return symbol_table.lookupLval(ident).type;
}

void LvalueNode::emitSource(std::string indent)
{
  std::cout << indent << ident;
}

RegisterPool::Register LvalueNode::emit()
{
  auto loc = symbol_table.lookupLval(ident);
  RegisterPool::Register reg;
  std::cout << "lw " << reg << ", " << loc.getLoc() << " # load ";
  emitSource("");
  std::cout << std::endl;
  return reg;
}

