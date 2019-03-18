#ifndef CONST_DECL_NODE_HPP
#define CONST_DECL_NODE_HPP

#include "Node.hpp"  // for Node
#include "Value.hpp" // for Value

#include <memory> // for shared_ptr
#include <string> // for string

class ExpressionNode;
class LiteralNode;

class ConstantDeclarationNode : public Node
{
public:
  ConstantDeclarationNode(std::string ident, ExpressionNode* type);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::string m_id;
  std::shared_ptr<LiteralNode> m_expr;
};

#endif
