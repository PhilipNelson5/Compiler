#include "VariableDeclarationNode.hpp"

#include <iostream>
#include <string.h>
#include <string>

VariableDeclarationNode::VariableDeclarationNode(ListNode<std::string>* identList,
                                                 TypeNode* type)
  : type(type)
{
  for (auto cur = std::shared_ptr<ListNode<std::string>>(identList); cur != nullptr;
       cur = cur->next)
  {
    idents.push_back(*(cur->data));
  }
}

void VariableDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent;
  for (auto i = 0u; i < idents.size() - 1; ++i)
  {
    std::cout << idents[i] << ", ";
  }
  std::cout << idents.back() << " : ";
  type->emitSource("");
  std::cout << ";" << std::endl;
}

RegisterPool::Register VariableDeclarationNode::emit()
{
  throw "not implemented";
}
