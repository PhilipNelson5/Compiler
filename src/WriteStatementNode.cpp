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
}

void WriteStatementNode::emmitSource(std::string indent)
{
  std::cout << indent << "write( ";
  for (auto&& expr : expressionList)
  {
    expr->emmitSource("");
  }
  std::cout << " );" << std::endl;
}

RegisterPool::Register WriteStatementNode::emmit()
{
  throw "not implemented";
}
