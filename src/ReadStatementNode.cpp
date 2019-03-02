#include "ReadStatementNode.hpp"

#include "SymbolTable.hpp"
#include "Type.hpp"
#include "log/easylogging++.h"

#include <iostream>

ReadStatementNode::ReadStatementNode(ListNode<LvalueNode>*& lVals)
  : lValues(ListNode<LvalueNode>::makeVector(lVals))
{}

void ReadStatementNode::emitSource(std::string indent)
{
  std::cout << indent << "read(";
  for (auto i = 0u; i < lValues.size() - 1; ++i)
  {
    lValues[i]->emitSource("");
    std::cout << ", ";
  }
  lValues.back()->emitSource("");
  std::cout << ");" << std::endl;
}

RegisterPool::Register ReadStatementNode::emit()
{
  std::cout << "\n# ";
  emitSource("");

  for (auto&& lval : lValues)
  {
    auto lval_info = symbol_table.lookupLval(lval->id);
    if (lval_info == nullptr)
    {
      LOG(ERROR) << lval->id << " is not an lvalue";
      exit(EXIT_FAILURE);
    }
    if (lval_info->type == IntegerType::get())
    {
      std::cout << "li $v0, 5"
                << " # load read integer instruction" << std::endl;
    }
    else if (lval_info->type == CharacterType::get())
    {
      std::cout << "li $v0, 12"
                << " # load read character instruction" << std::endl;
    }
    else
    {
      LOG(ERROR) << "type " << lval->type->name() << " can not be read into";
      exit(EXIT_FAILURE);
    }
    std::cout << "syscall" << std::endl;
    std::cout << "sw $v0, " << lval_info->getLoc();
    std::cout << " # " << lval->id << " = input" << std::endl << std::endl;
  }

  return {};
}

