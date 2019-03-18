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
  throw "not implemented NotNode";
}
