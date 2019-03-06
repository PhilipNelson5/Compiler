#include "IdentifierNode.hpp"

#include "BooleanLiteralNode.hpp"
#include "CharacterLiteralNode.hpp"
#include "IntegerLiteralNode.hpp"
#include "StringLiteralNode.hpp"
#include "SymbolTable.hpp"
#include "log/easylogging++.h"

#include <iostream>

IdentifierNode::IdentifierNode(std::string id)
  : LvalueNode(symbol_table.getType(id))
  , id(id)
{}

std::string IdentifierNode::getId()
{
  return id;
}

bool IdentifierNode::isConstant()
{
  return (symbol_table.lookupConst(id) != nullptr);
}

void IdentifierNode::emitSource(std::string indent)
{
  std::cout << indent << id;
}

Value IdentifierNode::emit()
{
  auto lval_info = symbol_table.lookupLval(id);
  if (lval_info != nullptr)
  {
    return {lval_info->offset, lval_info->memoryLocation};
  }

  auto const_info = symbol_table.lookupConst(id);
  if (const_info != nullptr)
  {
    return const_info->emit();
  }

  LOG(ERROR) << id << " is not defined";
  exit(EXIT_FAILURE);
}

