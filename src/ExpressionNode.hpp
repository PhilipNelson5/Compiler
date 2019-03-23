#ifndef EXPRESSION_NODE_HPP
#define EXPRESSION_NODE_HPP

#include "Node.hpp"  // for Node
#include "Value.hpp" // for Value

#include <memory> // for shared_ptr
class Type;

class ExpressionNode : public Node
{
public:
  ExpressionNode();
  ExpressionNode(std::shared_ptr<Type> type);
  virtual ~ExpressionNode() = default;

  virtual Value emit() = 0;
  virtual const std::shared_ptr<Type> getType();
  virtual void setType(std::shared_ptr<Type> t);
  virtual bool isLiteral() const;
  virtual bool isConstant() const;

protected:
  std::shared_ptr<Type> type;
};

#endif
