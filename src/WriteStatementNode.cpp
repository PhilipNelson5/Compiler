#include "WriteStatementNode.hpp"

#include <iostream>

WriteStatementNode::WriteStatementNode(ExpressionNode*& expr,
                                       ListNode<ExpressionNode>*& exprList)
{
  expressionList.emplace_back(expr);
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
  throw "not implemented";
}

RegisterPool::Register WriteStatementNode::emmit()
{
  throw "not implemented";
}
