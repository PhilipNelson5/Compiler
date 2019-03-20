#include "IfStatementNode.hpp"

#include "../fmt/include/fmt/core.h" // for print
#include "ExpressionNode.hpp"
#include "SymbolTable.hpp"

IfStatementNode::IfStatementNode(ExpressionNode*& ifExpr,
                                 ListNode<StatementNode>*& ifStatements)
  : ifStatement(std::make_pair<std::shared_ptr<ExpressionNode>,
                               std::vector<std::shared_ptr<StatementNode>>>(
      std::shared_ptr<ExpressionNode>(ifExpr),
      ListNode<StatementNode>::makeVector(ifStatements)))
{}

void IfStatementNode::emitSource(std::string indent)
{
  std::cout << indent << "if ";
  ifStatement.first->emitSource("");
  std::cout << " then\n";
  for (auto&& statement : ifStatement.second)
  {
    statement->emitSource(indent + "  ");
  }
  std::cout << indent << "end;\n";
}

Value IfStatementNode::emit()
{
  // --
  // if
  // --
  auto lblElse = symbol_table.newLabel("else");
  auto lblEnd = symbol_table.newLabel("end");
  auto r_ifExpr = ifStatement.first->emit().getTheeIntoARegister();
  fmt::print("beq {}, $0, {}\n", r_ifExpr, lblElse);

  for (auto&& statement : ifStatement.second)
  {
    statement->emit();
  }

  fmt::print("j {}\n", lblEnd);

  // ----
  // else
  // ----
  std::cout << lblElse << ":\n";

  // ---
  // end
  // ---
  std::cout << lblEnd << ":\n";

  return {};
}
