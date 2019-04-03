#include "FunctionCallNode.hpp"

void FunctionCallNode::emitSource(std::string indent)
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

Value FunctionCallNode::emit()
{
  return {};
}

bool FunctionCallNode::isConstant() const
{
  return false;
}

std::variant<std::monostate, int, char, bool> FunctionCallNode::eval() const
{
  return {};
}
