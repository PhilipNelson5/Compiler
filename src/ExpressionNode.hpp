#ifndef EXPRESSION_NODE_HPP
#define EXPRESSION_NODE_HPP

#include "Node.hpp"

class ExpressionNode : public Node
{
  virtual bool isLiteral();
};

#endif
