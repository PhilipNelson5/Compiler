#include "OrdinalExpressionNode.hpp"

#include "../fmt/include/fmt/core.h" // for format
#include "Type.hpp"                  // for IntegerType, CharacterType, Type
#include "Value.hpp"                 // for Value

#include <iostream> // for operator<<, cout, ostream, basi...
#include <stdlib.h> // for exit, EXIT_FAILURE

OrdinalExpressionNode::OrdinalExpressionNode(ExpressionNode*& expr)
  : ExpressionNode(IntegerType::get())
  , expr(expr)
{}

void OrdinalExpressionNode::emitSource(std::string indent)
{
  std::cout << indent << "ord(";
  expr->emitSource("");
  std::cout << ")";
}

Value OrdinalExpressionNode::emit()
{
  if (expr->getType() != CharacterType::get())
  {
    fmt::print("ord is not defined on {}. Must use character type",
                expr->getType()->name());
    exit(EXIT_FAILURE);
  }

  expr->setType(IntegerType::get());

  return expr->emit();
}
