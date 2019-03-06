#ifndef CONST_DECL_NODE_HPP
#define CONST_DECL_NODE_HPP

#include "LiteralNode.hpp"
#include "ListNode.hpp"
#include "Node.hpp"
#include "RegisterPool.hpp"

#include <memory>
#include <string>

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
