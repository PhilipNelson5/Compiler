#include "StringConstantNode.hpp"
#include "SymbolTable.hpp"

#include <iostream>

StringConstantNode::StringConstantNode(std::string string)
  : ExpressionNode(StringType::get()), string(string)
{}

void StringConstantNode::emitSource(std::string indent)
{
  std::cout << indent << string;
}

RegisterPool::Register StringConstantNode::emit()
{
  auto label = symbol_table.lookupString(string);
  RegisterPool::Register reg;
  std::cout << "la " << reg << ", " << label << std::endl;
  return reg;
}
