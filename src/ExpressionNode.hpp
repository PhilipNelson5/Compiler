#ifndef EXPRESSION_NODE_HPP
#define EXPRESSION_NODE_HPP

#include "Node.hpp"
#include "Type.hpp"

#include <memory>

class ExpressionNode : public Node
{
public:
  virtual bool isLiteral();

  ExpressionNode();

  ExpressionNode(std::shared_ptr<Type> type);

  const std::shared_ptr<Type> type;
};

#endif
