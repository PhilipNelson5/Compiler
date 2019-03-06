#include "OrdinalExpressionNode.hpp"

#include "Type.hpp"            // for IntegerType, CharacterType, Type
#include "Value.hpp"           // for Value
#include "log/easylogging++.h" // for Writer, CERROR, LOG

#include <iostream> // for operator<<, cout, ostream, basic_ostream
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
  if (expr->type != CharacterType::get())
  {
    LOG(ERROR) << "ord is not defined on " << expr->type->name()
               << ". Must use character type";
    exit(EXIT_FAILURE);
  }

  expr->type = IntegerType::get();

  return expr->emit();
}
