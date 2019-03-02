#include "LvalueNode.hpp"

#include "BooleanLiteralNode.hpp"
#include "CharacterLiteralNode.hpp"
#include "IntegerLiteralNode.hpp"
#include "SymbolTable.hpp"
#include "log/easylogging++.h"

#include <iostream>

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

RegisterPool::Register LvalueNode::emit()
{
  auto lval_info = symbol_table.lookupLval(id);
  if (lval_info != nullptr)
  {
    RegisterPool::Register result;
    std::cout << "lw " << result << ", " << lval_info->getLoc() << " # load "
              << id << '\n';

    return result;
  }

  auto const_info = symbol_table.lookupConst(id);
  if (const_info != nullptr)
  {
    if (const_info->type == IntegerType::get())
    {
      auto value = dynamic_cast<IntegerLiteralNode*>(const_info.get())->value;
      RegisterPool::Register result;
      std::cout << "li " << result << ", " << value << " # load " << id
                << ", value " << value << '\n';

      return result;
    }
    else if (const_info->type == BooleanType::get())
    {
      auto value = dynamic_cast<BooleanLiteralNode*>(const_info.get())->value;
      RegisterPool::Register result;
      std::cout << "li " << result << ", " << value << " # load " << id
                << ", value " << value << '\n';

      return result;
    }
    else if (const_info->type == CharacterType::get())
    {
      auto value
        = dynamic_cast<CharacterLiteralNode*>(const_info.get())->character;
      RegisterPool::Register result;
      std::cout << "li " << result << ", '" << value << "' # load " << id
                << ", value '" << value << "'\n";

      return result;
    }
    LOG(ERROR) << id << " is not a literal int, bool or char";
    exit(EXIT_FAILURE);
  }

  LOG(ERROR) << id << " is not defined";
  exit(EXIT_FAILURE);
}

