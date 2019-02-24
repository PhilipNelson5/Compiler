#include "ReadStatementNode.hpp"

#include "SymbolTable.hpp"
#include "Type.hpp"

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
    auto loc = symbol_table.lookupVariable(lval->ident);
    if (loc.type == IntegerType::get())
    {
      std::cout << "li $v0, 5"
                << " # load read integer instruction" << std::endl;
    }
    else if (loc.type == CharacterType::get())
    {
      std::cout << "li $v0, 12"
                << " # load read character instruction" << std::endl;
    }
    std::cout << "syscall" << std::endl;
    std::cout << "sw $v0, " << loc.getLoc();
    std::cout << " # " << lval->ident << " = input" << std::endl << std::endl;
  }

  return {};
}

