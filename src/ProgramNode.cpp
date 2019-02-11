#include "ProgramNode.hpp"

ProgramNode::ProgramNode(ListNode<VariableDeclarationNode>*& vds,
                         ListNode<StatementNode>*& mBlock)
{
  // Variable Declarations
  for (auto cur = std::make_shared<ListNode<VariableDeclarationNode>>(*vds);
       cur != nullptr;
       cur = cur->next)
  {
    varDecls.push_back(cur->data);
  }

  // Main Block
  for (auto cur = std::make_shared<ListNode<StatementNode>>(*mBlock);
       cur != nullptr;
       cur = cur->next)
  {
    mainBlock.push_back(cur->data);
  }
}

void ProgramNode::emmitSource()
{
  throw "not implemented";
}

RegisterPool::Register ProgramNode::emmit()
{
  throw "not implemented";
}

