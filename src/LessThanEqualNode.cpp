#include "LessThanEqualNode.hpp"

#include "../fmt/include/fmt/core.h" // for print
#include "RegisterPool.hpp" // for operator<<, Register
#include "Type.hpp"         // for BooleanType

#include <iostream> // for operator<<, ostream, cout, basic_ostream

LessThanEqualNode::LessThanEqualNode(ExpressionNode*& left,
                                     ExpressionNode*& right)
  : ExpressionNode(BooleanType::get())
  , lhs(left)
  , rhs(right)
{}

void LessThanEqualNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "<=";
  rhs->emitSource("");
}

Value LessThanEqualNode::emit()
{
  std::cout << "# ";
  emitSource("");
  std::cout << std::endl;

  auto v_lhs = lhs->emit();
  auto v_rhs = rhs->emit();
  auto r_lhs = v_lhs.getTheeIntoARegister();
  auto r_rhs = v_rhs.getTheeIntoARegister();
  RegisterPool::Register result;

  fmt::print("sle {}, {}, {}\n", result, r_lhs, r_rhs);

  return result;
}
