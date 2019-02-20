#include "ProgramNode.hpp"

#include <iostream>
#include <memory>

ProgramNode::ProgramNode(ListNode<ConstantDeclarationNode>*& cds,
                         ListNode<TypeDeclarationNode>*& tds,
                         ListNode<VariableDeclarationNode>*& vds,
                         ListNode<StatementNode>*& mBlock)
{
  // Constant Declarations
  // ---------------------
  for (auto cur = std::shared_ptr<ListNode<ConstantDeclarationNode>>(cds);
       cur != nullptr;
       cur = cur->next)
  {
    if (cur->data != nullptr) constantDecls.push_back(cur->data);
  }

  // Type Declarations
  // -----------------
  for (auto cur = std::shared_ptr<ListNode<TypeDeclarationNode>>(tds);
       cur != nullptr;
       cur = cur->next)
  {
    if (cur->data != nullptr) typeDecls.push_back(cur->data);
  }

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

void ProgramNode::emitSource(std::string indent)
{
  // Constant Declarations
  // ---------------------
  if (constantDecls.size() > 0u)
  {
    std::cout << indent << "CONST" << std::endl;
    for (auto&& constDecl : constantDecls)
    {
      constDecl->emitSource(indent + "  ");
    }
    std::cout << std::endl;
  }

  // Type Declarations
  // ---------------------
  if (varDecls.size() > 0)
  {
    std::cout << indent << "TYPE" << std::endl;
    for (auto&& typeDecl : typeDecls)
    {
      typeDecl->emitSource(indent + "  ");
    }
    std::cout << std::endl;
  }

  // Variable Declarations
  // ---------------------
  if (varDecls.size() > 0)
  {
    std::cout << indent << "VAR" << std::endl;
    for (auto&& varDecl : varDecls)
    {
      varDecl->emitSource(indent + "  ");
    }
    std::cout << std::endl;
  }

  // Main Block
  // ---------------------
  std::cout << indent << "BEGIN" << std::endl;
  for (auto&& statement : mainBlock)
  {
    statement->emitSource(indent + "  ");
  }
  std::cout << indent << "END." << std::endl;
}

RegisterPool::Register ProgramNode::emit()
{
  throw "not implemented";
}

