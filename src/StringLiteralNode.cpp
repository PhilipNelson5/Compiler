#include "StringLiteralNode.hpp"

#include "SymbolTable.hpp"

#include <iostream>

StringLiteralNode::StringLiteralNode(std::string string)
  : LiteralNode(StringType::get())
  , string(string)
{}

void StringLiteralNode::emitSource(std::string indent)
{
  std::cout << indent << string;
}

RegisterPool::Register StringLiteralNode::emit()
{
  auto label = symbol_table.lookupString(string);
  RegisterPool::Register reg;
  std::cout << "la " << reg << ", " << label << std::endl;
  return reg;
}
