#ifndef EXPRESSION_NODE_HPP
#define EXPRESSION_NODE_HPP

#include "Node.hpp"
#include "Type.hpp"

#include <memory>

class ExpressionNode : public Node
{
public:
  virtual bool isLiteral();
  virtual std::shared_ptr<Type> type() { return IntegerType::get(); }
};

#endif
