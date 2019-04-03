#include "ProcedureCallNode.hpp"

void ProcedureCallNode::emitSource(std::string indent)
{
  std::cout << indent << " " << id << "(";
  if (args.size() > 0)
  {
    if (args.size() > 1)
      for (auto i = 0u; i < args.size() - 1; ++i)
      {
        args[i]->emitSource("");
        std::cout << ", ";
      }
    args.back()->emitSource("");
  }
  std::cout << ");\n";
}

void ProcedureCallNode::emit() {}
