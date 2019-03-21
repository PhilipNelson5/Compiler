#include "SuccessorExpressionNode.hpp"

#include "../fmt/include/fmt/core.h" // for print
#include "SymbolTable.hpp"
#include "Type.hpp"
#include "log/easylogging++.h"

#include <iostream>

SuccessorExpressionNode::SuccessorExpressionNode(ExpressionNode*& expr)
  : ExpressionNode(expr->type)
  , expr(expr)
{}

void SuccessorExpressionNode::emitSource(std::string indent)
{
  std::cout << indent << "succ(";
  expr->emitSource("");
  std::cout << ")";
}

Value SuccessorExpressionNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << '\n';

  if (expr->type == BooleanType::get())
  {
    auto r_expr = expr->emit().getTheeIntoARegister();
    fmt::print("xori {}, 1\n", r_expr);
    return r_expr;
  }
  else if (expr->type == IntegerType::get() || expr->type == CharacterType::get())
  {
    auto r_expr = expr->emit().getTheeIntoARegister();
    fmt::print("addi {0}, {0}, 1\n", r_expr);
    return r_expr;
  }
  else
  {
    LOG(ERROR) << fmt::format("succ is not defined for type {}", expr->type->name());
    exit(EXIT_FAILURE);
  }
}
