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
  else if (expr->type == IntegerType::get())
  {
    auto r_expr = expr->emit().getTheeIntoARegister();
    fmt::print("addi {0}, {0}, 1\n", r_expr);
    return r_expr;
  }
  else if (expr->type == CharacterType::get())
  {
    auto r_expr = expr->emit().getTheeIntoARegister();
    // auto lblEnd = symbol_table.newLabel("end");
    // auto lblInc = symbol_table.newLabel("increment");
    // RegisterPool::Register r_char;
    // RegisterPool::Register r_noWrap;

    // check lower case
    // fmt::print("li {}, 'z'\n", r_char);
    // fmt::print("seq {}, {}, {}\n", r_noWrap, r_expr, r_char);
    // fmt::print("beq {}, $0, {}\n", r_noWrap, lblInc);
    // wrap lower
    // fmt::print("li {}, 'a'\n", r_expr);
    // fmt::print("j {}\n", lblEnd);

    // check upper case
    // fmt::print("li {}, 'Z'\n", r_char);
    // fmt::print("seq {}, {}, {}\n", r_noWrap, r_expr, r_char);
    // fmt::print("beq {}, $0, {}\n", r_noWrap, lblInc);
    // wrap upper
    // fmt::print("li {}, 'A'\n", r_expr);
    // fmt::print("j {}\n", lblEnd);

    // std::cout << lblInc << ":\n";
    fmt::print("addi {0}, {0}, 1\n", r_expr);

    // std::cout << lblEnd << ":\n";

    return r_expr;
  }
  else
  {
    LOG(ERROR) << fmt::format("succ is not defined for type {}", expr->type->name());
    exit(EXIT_FAILURE);
  }
}
