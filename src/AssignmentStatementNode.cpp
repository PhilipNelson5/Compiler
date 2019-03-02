#include "AssignmentStatementNode.hpp"

#include "SymbolTable.hpp"
#include "log/easylogging++.h"

#include <iostream>

AssignmentStatementNode::AssignmentStatementNode(LvalueNode*& lval,
                                                 ExpressionNode* expr)
  : lval(std::shared_ptr<LvalueNode>(lval))
  , expr(std::shared_ptr<ExpressionNode>(expr))
{}

void AssignmentStatementNode::emitSource(std::string indent)
{
  std::cout << indent;
  lval->emitSource("");
  std::cout << " := ";
  expr->emitSource("");
  std::cout << ";" << std::endl;
}

RegisterPool::Register AssignmentStatementNode::emit()
{
  std::cout << "\n# ";
  emitSource("");

  auto lval_info = symbol_table.lookupLval(lval->id);
  if (lval_info == nullptr)
  {
    LOG(ERROR) << lval->id << " is not an lvalue";
    exit(EXIT_FAILURE);
  }
  auto reg_expr = expr->emit();

  std::cout << "sw " << reg_expr << ", " << lval_info->getLoc();

  std::cout << " # ";
  emitSource("");

  return reg_expr;
}
