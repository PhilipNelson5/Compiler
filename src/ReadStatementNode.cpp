#include "ReadStatementNode.hpp"

#include <iostream>

ReadStatementNode::ReadStatementNode(ListNode<LvalueNode>*& lVals)
  : lValues(ListNode<LvalueNode>::makeVector(lVals))
{}

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

