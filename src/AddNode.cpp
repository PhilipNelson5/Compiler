#include "AddNode.hpp"

#include "../fmt/include/fmt/core.h" // for print, format
#include "IntegerLiteralNode.hpp"    // for IntegerLiteralNode
#include "RegisterPool.hpp"          // for Register
#include "Type.hpp"                  // for IntegerType, Type, CharacterType
#include "log/easylogging++.h"       // for Writer, CERROR, LOG

#include <iostream> // for operator<<, cout, ostream

AddNode::AddNode(ExpressionNode*& left, ExpressionNode*& right)
  : ExpressionNode(IntegerType::get())
  , lhs(left)
  , rhs(right)
{}

void AddNode::emitSource(std::string indent)
{
  std::cout << indent;
  lhs->emitSource("");
  std::cout << "+";
  rhs->emitSource("");
}

Value AddNode::emit()
{
  if (lhs->type != rhs->type)
  {
    LOG(ERROR) << fmt::format("mismatched types in add expression: {} and {}",
                              lhs->type->name(),
                              rhs->type->name());
  }

  if (lhs->type != IntegerType::get() && lhs->type != CharacterType::get())
  {
    LOG(ERROR) << "can not add non integer types";
  }

  std::cout << "# ";
  emitSource("");
  std::cout << '\n';

  if (lhs->isConstant())
  {
    auto lhs_const = dynamic_cast<IntegerLiteralNode*>(lhs.get());
    auto v_rhs = rhs->emit();
    auto r_rhs = v_rhs.getTheeIntoARegister();
    RegisterPool::Register result;

    fmt::print("addi {0}, {1}, {2} # ", result, lhs_const->value, r_rhs);

    emitSource("");
    std::cout << '\n';

    return result;
  }
  else if (rhs->isConstant())
  {
    auto rhs_const = dynamic_cast<IntegerLiteralNode*>(rhs.get());
    auto v_lhs = lhs->emit();
    auto r_lhs = v_lhs.getTheeIntoARegister();
    RegisterPool::Register result;

    fmt::print("addi {0}, {1}, {2} # ", result, r_lhs, rhs_const->value);

    emitSource("");
    std::cout << '\n';

    return result;
  }
  else
  {
    auto v_lhs = lhs->emit();
    auto v_rhs = rhs->emit();
    auto r_lhs = v_lhs.getTheeIntoARegister();
    auto r_rhs = v_rhs.getTheeIntoARegister();
    RegisterPool::Register result;

    fmt::print("add {0}, {1}, {2} # ", result, r_lhs, r_rhs);

    emitSource("");
    std::cout << '\n';

    return result;
  }
}
