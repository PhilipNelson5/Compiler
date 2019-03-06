#include "IdentifierNode.hpp"

#include "LiteralNode.hpp"     // for LiteralNode
#include "SymbolTable.hpp"     // for SymbolTable, symbol_table, Variable
#include "log/easylogging++.h" // for Writer, CERROR, LOG

#include <iostream> // for basic_ostream, cout, ostream
#include <memory>   // for operator!=, shared_ptr, __shared_ptr_...
#include <stdlib.h> // for exit, EXIT_FAILURE

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

