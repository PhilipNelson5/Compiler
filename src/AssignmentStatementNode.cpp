#include "AssignmentStatementNode.hpp"

#include "ExpressionNode.hpp"  // for ExpressionNode
#include "IdentifierNode.hpp"  // for IdentifierNode
#include "RegisterPool.hpp"    // for operator<<
#include "SymbolTable.hpp"     // for SymbolTable, Variable, symbol_table
#include "log/easylogging++.h" // for Writer, CERROR, LOG

#include <iostream> // for operator<<, ostream, cout, basic_ostream
#include <stdlib.h> // for exit, EXIT_FAILURE

AssignmentStatementNode::AssignmentStatementNode(LvalueNode*& identifier,
                                                 ExpressionNode* expr)
  : identifier(std::shared_ptr<LvalueNode>(identifier))
  , expr(std::shared_ptr<ExpressionNode>(expr))
{}

void AssignmentStatementNode::emitSource(std::string indent)
{
  std::cout << indent;
  identifier->emitSource("");
  std::cout << " := ";
  expr->emitSource("");
  std::cout << ";\n";
}

Value AssignmentStatementNode::emit()
{
  std::cout << "\n# ";
  emitSource("");

  auto v_id = identifier->emit();
  if (!v_id.isLvalue())
  {
    LOG(ERROR) << identifier->getId() << " is not an Lvalue";
    exit(EXIT_FAILURE);
  }
  auto v_expr = expr->emit();
  auto r_expr = v_expr.getTheeIntoARegister();

  std::cout << "sw " << r_expr << ", " << v_id.getLocation();

  std::cout << " # ";
  emitSource("");

  return r_expr;
}
