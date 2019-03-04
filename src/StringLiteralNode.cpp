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

Value StringLiteralNode::emit()
{
  return symbol_table.lookupString(string);
}
