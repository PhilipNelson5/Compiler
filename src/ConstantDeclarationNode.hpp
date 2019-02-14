#ifndef CONST_DECL_NODE_HPP
#define CONST_DECL_NODE_HPP

#include "ExpressionNode.hpp"
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
  virtual RegisterPool::Register emit() override;

private:
  std::string ident;
  std::shared_ptr<ExpressionNode> expr;
};

#endif
