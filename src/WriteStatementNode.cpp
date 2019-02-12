#include "WriteStatementNode.hpp"

#include <iostream>

WriteStatementNode::WriteStatementNode(ListNode<ExpressionNode>*& exprList)
{
  for (auto cur = std::make_shared<ListNode<ExpressionNode>>(*exprList);
       cur != nullptr;
       cur = cur->next)
  {
    expressionList.emplace_back(cur->data);
  }
  std::cout << "Write Statement Node constructed with " << expressionList.size()
            << " statements" << std::endl;
}

void WriteStatementNode::emmitSource()
{
  std::cout << "Write Statement" << std::endl;
}

RegisterPool::Register WriteStatementNode::emmit()
{
  throw "not implemented";
}
