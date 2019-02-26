#include "AssignmentStatementNode.hpp"

#include "SymbolTable.hpp"

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

  auto loc = symbol_table.lookupLval(lval->ident);
  auto reg_expr = expr->emit();

  std::cout << "sw " << reg_expr << ", " << loc.getLoc();

  std::cout << " # ";
  emitSource("");

  return reg_expr;
}
