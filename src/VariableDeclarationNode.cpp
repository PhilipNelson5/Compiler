#include "VariableDeclarationNode.hpp"

#include <iostream>
#include <string.h>
#include <string>

VariableDeclarationNode::VariableDeclarationNode(ListNode<std::string>* identList,
                                                 char* type)
  : type(type)
{
  std::cout << "new VariableDeclarationNode" << std::endl;
  for (auto cur = std::shared_ptr<ListNode<std::string>>(identList); cur != nullptr;
       cur = cur->next)
  {
    idents.push_back(*(cur->data));
    std::cout << idents.back() << std::endl;
  }
}

void VariableDeclarationNode::emmitSource(std::string indent)
{
  std::cout << indent;
  for (auto i = 0u; i < idents.size() - 1; ++i)
  {
    std::cout << idents[i] << ", ";
  }
  std::cout << idents.back() << " : " << type << ";" << std::endl;
}

RegisterPool::Register VariableDeclarationNode::emmit()
{
  throw "not implemented";
}
