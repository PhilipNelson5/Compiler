#include "WriteStatementNode.hpp"

#include "log/easylogging++.h"

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

Value WriteStatementNode::emit()
{
  std::cout << "\n# ";
  emitSource("");

  for (auto&& expr : expressionList)
  {
    auto v_reg = expr->emit();

    if (expr->type == IntegerType::get() | expr->type == BooleanType::get())
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
    else
    {
      LOG(ERROR) << "write is not defined for type " << expr->type->name();
      exit(EXIT_FAILURE);
    }

    auto r_reg = v_reg.getTheeIntoARegister();
    std::cout << "or $a0, $0, " << r_reg << " # ";
    std::cout << "write(";
    expr->emitSource("");
    std::cout << ")" << std::endl;
    std::cout << "syscall" << std::endl << std::endl;
  }

  return {};
}
