#include "VariableDeclarationNode.hpp"

#include <string.h>

VariableDeclarationNode::VariableDeclarationNode(ListNode<char*>* identList,
                                                 char* type)
  : type(type)
{
  for (auto cur = std::make_shared<ListNode<char*>>(*identList); cur != nullptr;
       cur = cur->next)
  {
    idents.emplace_back(strdup(*cur->data));
  }
}

void VariableDeclarationNode::emmitSource() {}

RegisterPool::Register VariableDeclarationNode::emmit()
{
  throw "not implemented";
}
