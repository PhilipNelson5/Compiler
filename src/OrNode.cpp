#include "OrNode.hpp"

#include "../fmt/include/fmt/core.h" // for print
#include "Type.hpp"                  // for BooleanType

#include <iostream> // for operator<<, cout, ostream

OrNode::OrNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(BooleanType::get())
  , lhs(left)
  , rhs(right)
{}

bool OrNode::isConstant() const
{
  return lhs->isConstant() && rhs->isConstant();
}

std::variant<std::monostate, int, char, bool> OrNode::eval() const
{
  auto var_lhs = lhs->eval();
  auto var_rhs = rhs->eval();

  if (var_lhs.index() != var_rhs.index())
  {
    LOG(ERROR) << fmt::format(
      "Type mismatch, can not or {} | {}", lhs->getType()->name(), rhs->getType()->name());
    exit(EXIT_FAILURE);
  }
  if ((var_lhs.index() == 0) || (var_rhs.index() == 0))
  {
    return {};
  }
  if (std::holds_alternative<int>(var_lhs))
  {
    return std::get<int>(var_lhs) | std::get<int>(var_rhs);
  }
  if (std::holds_alternative<char>(var_lhs))
  {
    return std::get<char>(var_lhs) | std::get<char>(var_rhs);
  }
  if (std::holds_alternative<bool>(var_lhs))
  {
    return std::get<bool>(var_lhs) || std::get<bool>(var_rhs);
  }
  return {};
}

void OrNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "|";
  rhs->emitSource("");
}

Value OrNode::emit()
{
  auto v_lhs = lhs->emit();
  auto v_rhs = rhs->emit();
  auto r_lhs = v_lhs.getTheeIntoARegister();
  auto r_rhs = v_rhs.getTheeIntoARegister();
  RegisterPool::Register result;

  fmt::print("or {}, {}, {}\n", result, r_lhs, r_rhs);

  return result;
}
