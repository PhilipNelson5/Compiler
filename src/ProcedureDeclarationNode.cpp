#include "ProcedureDeclarationNode.hpp"

#include "../fmt/include/fmt/core.h"

void ProcedureDeclarationNode::emitSource(std::string indent)
{
  std::cout << indent << "PROCEDURE " << id << "(";

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

  std::cout << ");\n";

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

void ProcedureDeclarationNode::emit() {}
