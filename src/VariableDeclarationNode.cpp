#include "VariableDeclarationNode.hpp"

#include <iostream>
#include <string.h>
#include <string>

VariableDeclarationNode::VariableDeclarationNode(
  ListNode<std::string>* identList,
  TypeNode* type)
  : idents(ListNode<std::string>::makeDerefVector(identList))
  , type(type)
{}

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
