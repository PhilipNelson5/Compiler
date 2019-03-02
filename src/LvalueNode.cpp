#include "LvalueNode.hpp"

#include "BooleanLiteralNode.hpp"
#include "CharacterLiteralNode.hpp"
#include "IntegerLiteralNode.hpp"
#include "SymbolTable.hpp"
#include "log/easylogging++.h"

#include <iostream>

LvalueNode::LvalueNode(std::string ident)
  : ExpressionNode(nullptr)
  , ident(ident)
{}

bool LvalueNode::isConstant()
{
  return (symbol_table.lookupConst(ident) != nullptr);
}

void LvalueNode::emitSource(std::string indent)
{
  std::cout << indent << ident;
}

RegisterPool::Register LvalueNode::emit()
{
  auto lval_info = symbol_table.lookupLval(ident);
  if (lval_info != nullptr)
  {
    // TRICKY: As far as I can tell the type can not be set at construction time
    //         so when the lValue is emitted, look up the type and set it
    type = lval_info->type;
    RegisterPool::Register result;
    std::cout << "lw " << result << ", " << lval_info->getLoc() << " # load "
              << ident << '\n';

    return result;
  }

  auto const_info = symbol_table.lookupConst(ident);
  if (const_info != nullptr)
  {
    // TRICKY: As far as I can tell the type can not be set at construction time
    //         so when the lValue is emitted, look up the type and set it
    type = const_info->type;
    if (const_info->type == IntegerType::get())
    {
      auto value = dynamic_cast<IntegerLiteralNode*>(const_info.get())->value;
      RegisterPool::Register result;
      std::cout << "li " << result << ", " << value << " # load " << ident
                << ", value " << value << '\n';

      return result;
    }
    else if (const_info->type == BooleanType::get())
    {
      auto value = dynamic_cast<BooleanLiteralNode*>(const_info.get())->value;
      RegisterPool::Register result;
      std::cout << "li " << result << ", " << value << " # load " << ident
                << ", value " << value << '\n';

      return result;
    }
    else if (const_info->type == CharacterType::get())
    {
      auto value
        = dynamic_cast<CharacterLiteralNode*>(const_info.get())->character;
      RegisterPool::Register result;
      std::cout << "li " << result << ", '" << value << "' # load " << ident
                << ", value '" << value << "'\n";

      return result;
    }
    LOG(ERROR) << ident << " is not a literal int, bool or char";
    exit(EXIT_FAILURE);
  }

  LOG(ERROR) << ident << " is not defined";
  exit(EXIT_FAILURE);
}

