#include "DivideNode.hpp"

#include "RegisterPool.hpp"    // for operator<<, Register
#include "Type.hpp"            // for IntegerType, Type
#include "log/easylogging++.h" // for Writer, CERROR, LOG

#include <iostream> // for operator<<, ostream, cout, basic_ostream

DivideNode::DivideNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , lhs(left)
  , rhs(right)
{}

void DivideNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "/";
  rhs->emitSource("");
}

Value DivideNode::emit()
{
  if (lhs->type != rhs->type)
  {
    LOG(ERROR) << fmt::format(
      "mismatched types in divide expression: {} and {}",
      lhs->type->name(),
      rhs->type->name());
  }

  if (lhs->type != IntegerType::get())
  {
    LOG(ERROR) << "can not divide non integer types";
  }

  std::cout << "# ";
  emitSource("");
  std::cout << '\n';

  auto v_lhs = lhs->emit();
  auto v_rhs = rhs->emit();
  auto r_lhs = v_lhs.getTheeIntoARegister();
  auto r_rhs = v_rhs.getTheeIntoARegister();
  RegisterPool::Register result;

  fmt::print("div {}, {}\n", r_lhs, r_rhs);
  fmt::print("mflo {} # ", result);
  emitSource("");
  std::cout << '\n';

  return result;
}
