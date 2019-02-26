#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "AddNode.hpp"
#include "ExpressionNode.hpp"
#include "IntegerConstantNode.hpp"

#include <iostream>

ExpressionNode* makeAddNode(ExpressionNode* e1, ExpressionNode* e2)
{
  if (e1->isLiteral() && e2->isLiteral())
  {
    return new IntegerConstantNode(
      dynamic_cast<IntegerConstantNode*>(e1)->value
      + dynamic_cast<IntegerConstantNode*>(e2)->value);
  }
  else
    return new AddNode(e1, e2);
}

#endif
