#ifndef TYPE_DECLARATION_NODE_HPP
#define TYPE_DECLARATION_NODE_HPP

#include "Node.hpp"
#include "TypeNode.hpp"

class TypeDeclarationNode : public Node
{
public:
  TypeDeclarationNode(std::string ident, TypeNode* type);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;

private:
  std::string ident;
  std::shared_ptr<TypeNode> type;
};

#endif
