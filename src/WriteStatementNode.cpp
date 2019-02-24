#include "WriteStatementNode.hpp"

#include <iostream>

WriteStatementNode::WriteStatementNode(ListNode<ExpressionNode>*& exprList)
  : expressionList(ListNode<ExpressionNode>::makeVector(exprList))
{}

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
  std::cout << "\n# ";
  emitSource("");

  for (auto&& expr : expressionList)
  {
    if (expr->type == IntegerType::get())
    {
      auto reg = expr->emit();
      std::cout << "li $v0, 1"
                << " # load print integer instruction" << std::endl;
      std::cout << "or $a0, $0, " << reg << " # ";
      emitSource("");
      std::cout << "syscall" << std::endl;
    }
  }

  return {};
}
