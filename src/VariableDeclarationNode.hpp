#ifndef VARIABLE_DECLARATION_NODE_HPP
#define VARIABLE_DECLARATION_NODE_HPP

#include "ListNode.hpp"
#include "Node.hpp"
#include "RegisterPool.hpp"
#include "TypeNode.hpp"

#include <string>
#include <vector>

class VariableDeclarationNode : public Node
{
public:
  VariableDeclarationNode(ListNode<std::string>* identList, TypeNode* type);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::vector<std::string> m_ids;
  std::shared_ptr<TypeNode> m_type;
};

#endif
