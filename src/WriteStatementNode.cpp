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
    auto reg = expr->emit();

    if (expr->type == IntegerType::get())
    {
      std::cout << "li $v0, 1"
                << " # load print integer instruction" << std::endl;
    }
    else if (expr->type == CharacterType::get())
    {
      std::cout << "li $v0, 11"
                << " # load print character instruction" << std::endl;
    }
    else if (expr->type == StringType::get())
    {
      std::cout << "li $v0, 4"
                << " # load print string instruction" << std::endl;
    }

    std::cout << "or $a0, $0, " << reg << " # ";
    std::cout << "write(";
    expr->emitSource("");
    std::cout << ")" << std::endl;
    std::cout << "syscall" << std::endl << std::endl;
  }

  return {};
}
