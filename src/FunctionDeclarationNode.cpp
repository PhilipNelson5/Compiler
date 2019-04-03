#include "FunctionDeclarationNode.hpp"

#include "../fmt/include/fmt/core.h"

void FunctionDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent << "FUNCTION " << id << "(";

  if (parameters.size() > 0)
  {
    if (parameters.size() > 1)
      for (auto i = 0u; i < parameters.size() - 1; ++i)
      {
        parameters[i]->emitSource("");
        std::cout << "; ";
      }
    parameters.back()->emitSource("");
  }

  std::cout << ") :" << getType()->name() << "; ";

  if (body == nullptr)
  {
    std::cout << "forward;\n";
  }
  else
  {
    std::cout << indent << "BEGIN\n";
    body->emitSource(indent + "  ");
    std::cout << indent << "END;\n";
  }
}

void FunctionDeclarationNode::emit() {}

std::shared_ptr<Type> FunctionDeclarationNode::getType()
{
  if(returnType == nullptr)
  {
    returnType = returnTypeNode->getType();
  }
  return returnType;
}
