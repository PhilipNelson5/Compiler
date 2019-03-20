#include "ForStatementNode.hpp"

#include "SymbolTable.hpp"
#include "log/easylogging++.h"

ForStatementNode::ForStatementNode(char*& id,
                                   ExpressionNode*& startExpr,
                                   ExpressionNode*& endExpr,
                                   ListNode<StatementNode>*& statements,
                                   Type type)
  : id(id)
  , startExpr(startExpr)
  , endExpr(endExpr)
  , statements(ListNode<StatementNode>::makeVector(statements))
  , type(type)
{
  LOG(DEBUG) << "NEW FOR_STATEMENT_NODE (" << id << ")";
  if (!symbol_table.lookupLval(id))
  {
    LOG(DEBUG) << "insert " << id;
    symbol_table.storeVariable(id, startExpr->type);
  }
}

void ForStatementNode::emitSource(std::string indent)
{
  // symbol_table.enter_scope();

  std::cout << indent << "for ";
  startExpr->emitSource("");
  std::cout << (type == Type::TO ? " to " : " downto ");
  endExpr->emitSource("");
  std::cout << " do\n";

  for (auto&& statement : statements)
  {
    statement->emitSource(indent + "  ");
  }

  std::cout << indent << "end;";
  // symbol_table.exit_scope();
}

Value ForStatementNode::emit()
{
  return {};
}
