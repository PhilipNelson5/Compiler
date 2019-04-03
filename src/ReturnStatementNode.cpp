#include "ReturnStatementNode.hpp"

void ReturnStatementNode::emitSource(std::string indent)
{
  if (expr != nullptr)
  {
    std::cout << indent << "return ";
    expr->emitSource("");
    std::cout << ";\n";
  }
  else
  {
    std::cout << indent << "return;\n";
  }
}

void ReturnStatementNode::emit() {}

