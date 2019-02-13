#include "ProgramNode.hpp"

#include <iostream>
#include <memory>

ProgramNode::ProgramNode(ListNode<VariableDeclarationNode>*& vds,
                         ListNode<StatementNode>*& mBlock)
{
  // Variable Declarations
  // ---------------------
  for (auto cur = std::shared_ptr<ListNode<VariableDeclarationNode>>(vds);
       cur != nullptr;
       cur = cur->next)
  {
    if (cur->data != nullptr) varDecls.push_back(cur->data);
  }

  // Main Block
  // ----------
  for (auto cur = std::shared_ptr<ListNode<StatementNode>>(mBlock);
       cur != nullptr;
       cur = cur->next)
  {
    if (cur->data != nullptr) mainBlock.push_back(cur->data);
  }

}

void ProgramNode::emmitSource(std::string indent)
{
  // Variable Declarations
  // ---------------------
  std::cout << indent << "VAR" << std::endl;
  for (auto&& varDecl : varDecls)
  {
    varDecl->emmitSource(indent + "  ");
  }
  std::cout << std::endl;

  // Main Block
  // ---------------------
  std::cout << indent << "BEGIN" << std::endl;
  for (auto&& statement : mainBlock)
  {
    statement->emmitSource(indent + "  ");
  }
  std::cout << indent << "END." << std::endl;
}

RegisterPool::Register ProgramNode::emmit()
{
  throw "not implemented";
}

