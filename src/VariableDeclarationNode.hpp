#ifndef VARIABLE_DECLARATION_NODE_HPP
#define VARIABLE_DECLARATION_NODE_HPP

#include "ListNode.hpp"
#include "Node.hpp"
#include "RegisterPool.hpp"

#include <string>
#include <vector>

class VariableDeclarationNode : public Node
{
public:
  VariableDeclarationNode(ListNode<std::string>* identList, char* type);
  virtual void emmitSource(std::string indent) override;
  virtual RegisterPool::Register emmit() override;

private:
  std::vector<std::string> idents;
  std::string type;
};

#endif
