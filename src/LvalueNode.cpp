#include "LvalueNode.hpp"

#include "BooleanLiteralNode.hpp"
#include "CharacterLiteralNode.hpp"
#include "IntegerLiteralNode.hpp"
#include "StringLiteralNode.hpp"
#include "SymbolTable.hpp"
#include "log/easylogging++.h"

#include <iostream>

namespace
{
std::shared_ptr<Type> getType(std::string identifier)
{
  auto lval_info = symbol_table.lookupLval(identifier);
  if (lval_info != nullptr)
  {
    return lval_info->type;
  }

  auto const_info = symbol_table.lookupConst(identifier);
  if (const_info != nullptr)
  {
    return const_info->type;
  }

  LOG(ERROR) << identifier << " is not defined";
  exit(EXIT_FAILURE);
}

} // namespace

LvalueNode::LvalueNode(std::string _id)
  : ExpressionNode(getType(_id))
  , id(_id)
{}

bool LvalueNode::isConstant()
{
  return (symbol_table.lookupConst(id) != nullptr);
}

void LvalueNode::emitSource(std::string indent)
{
  std::cout << indent << id;
}

Value LvalueNode::emit()
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

