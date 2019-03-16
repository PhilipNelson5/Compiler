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
  auto v_expr = expr->emit();
  // auto size = expr->type->size();
  // assign(v_expr, v_id, size);
  if (v_id.isLvalue())
  {
    if (ArrayType* array = dynamic_cast<ArrayType*>(expr->type.get()))
    {
      auto size = array->size();
      auto r_expr = v_expr.getRegister();
      auto [offset, memoryLocation] = std::get<std::pair<int, int>>(v_id.value);
      RegisterPool::Register tmp;
      std::cout << "# Deep Copy\n";
      for (auto i = 0; i < size; i += 4)
      {
        std::cout << "lw " << tmp << ", " << i << "(" << r_expr << ")"
                  << " # copy\n";
        std::cout << "sw " << tmp << ", " << offset + i << "($"
                  << memoryLocation << ")"
                  << " # paste\n";
      }
    }
    else
    {
      auto r_expr = v_expr.getTheeIntoARegister();
      std::cout << "sw " << r_expr << ", " << v_id.getLocation();
    }
  }
  else if (v_id.isRegister())
  {
    auto r_id = v_id.getRegister();
    auto r_expr = v_expr.getTheeIntoARegister();
    std::cout << "sw " << r_expr << ", 0(" << r_id << ")";
  }
  else
  {
    LOG(ERROR) << identifier->getId() << " is not an Lvalue";
    exit(EXIT_FAILURE);
  }
  std::cout << " # ";
  emitSource("");

  // return r_expr;
  return {};
}
