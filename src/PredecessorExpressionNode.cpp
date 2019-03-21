#include "PredecessorExpressionNode.hpp"

#include "Type.hpp"

#include <iostream> // for operator<<, char_traits, cout, ostream, basic_os...

PredecessorExpressionNode::PredecessorExpressionNode(ExpressionNode*& expr)
  : ExpressionNode(expr->type)
  , expr(expr)
{}

void PredecessorExpressionNode::emitSource(std::string indent)
{
  std::cout << indent << "pred(";
  expr->emitSource("");
  std::cout << ")";
}

Value PredecessorExpressionNode::emit()
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
    fmt::print("addi {0}, {0}, -1\n", r_expr);
    return r_expr;
  }
  else
  {
    LOG(ERROR) << fmt::format("pred is not defined for type {}", expr->type->name());
    exit(EXIT_FAILURE);
  }
}
