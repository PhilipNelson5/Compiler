#ifndef TYPE_DECLARATION_NODE_HPP
#define TYPE_DECLARATION_NODE_HPP

#include "Node.hpp" // for Node
#include "Type.hpp"
#include "TypeNode.hpp"
#include "Value.hpp" // for Value

#include <memory> // for shared_ptr
#include <string> // for string
class Type;

class TypeDeclarationNode : public Node
{
public:
  TypeDeclarationNode(std::string ident, TypeNode*& type);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::string m_id;
  std::shared_ptr<Type> m_type;
};

#endif
