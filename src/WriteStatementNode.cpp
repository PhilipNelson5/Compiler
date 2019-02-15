#include "WriteStatementNode.hpp"

#include <iostream>

WriteStatementNode::WriteStatementNode(ListNode<ExpressionNode>*& exprList)
{
  for (auto cur = std::make_shared<ListNode<ExpressionNode>>(*exprList);
       cur != nullptr;
       cur = cur->next)
  {
    if (cur->data != nullptr) expressionList.emplace_back(cur->data);
  }
}

void WriteStatementNode::emitSource(std::string indent)
{
  std::cout << indent << "write(";
  for (auto i = 0u; i < expressionList.size() - 1; ++i)
  {
    expressionList[i]->emitSource("");
    std::cout << ", ";
  }
  expressionList.back()->emitSource("");
  std::cout << ");" << std::endl;
}

RegisterPool::Register WriteStatementNode::emit()
{
  throw "not implemented";
}
