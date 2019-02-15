#include "ReadStatementNode.hpp"

#include <iostream>

ReadStatementNode::ReadStatementNode(ListNode<LvalueNode>*& lVals)
{
  for (auto cur = std::make_shared<ListNode<LvalueNode>>(*lVals);
       cur != nullptr;
       cur = cur->next)
  {
    if (cur->data != nullptr) lValues.emplace_back(cur->data);
  }
}

void ReadStatementNode::emitSource(std::string indent)
{
  std::cout << indent << "read(";
  for (auto i = 0u; i < lValues.size() - 1; ++i)
  {
    lValues[i]->emitSource("");
    std::cout << ", ";
  }
  lValues.back()->emitSource("");
  std::cout << ");" << std::endl;
}

RegisterPool::Register ReadStatementNode::emit()
{
  throw "not implemented";
}

