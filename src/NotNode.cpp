#include "NotNode.hpp"

#include "Type.hpp" // for IntegerType

#include <iostream> // for operator<<, cout, ostream

NotNode::NotNode(ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , rhs(right)
{}

void NotNode::emitSource(std::string indent)
{
  std::cout << indent;
  std::cout << "~";
  rhs->emitSource("");
}

Value NotNode::emit()
{
  auto v_rhs = rhs->emit();
  auto r_rhs = v_rhs.getTheeIntoARegister();
  RegisterPool::Register result;

  fmt::print("not {}, {}\n", result, r_rhs);

  return result;
}
