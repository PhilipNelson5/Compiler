#include "StringLiteralNode.hpp"

#include "SymbolTable.hpp"
#include "log/easylogging++.h"

#include <iostream>

StringLiteralNode::StringLiteralNode(std::string string)
  : LiteralNode(StringType::get())
  , string(string)
{
  LOG(DEBUG) << "NEW STRING NODE";
}

void StringLiteralNode::emitSource(std::string indent)
{
  std::cout << indent << string;
}

RegisterPool::Register StringLiteralNode::emit()
{
  auto label = symbol_table.lookupString(string);
  RegisterPool::Register result;
  std::cout << "la " << result << ", " << label << std::endl;
  return result;
}
