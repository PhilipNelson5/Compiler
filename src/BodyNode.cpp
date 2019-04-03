#include "BodyNode.hpp"

void BodyNode::emitSource(std::string indent)
{
  if (!constDecls.empty())
  {
    for (auto&& constDecl : constDecls)
    {
      constDecl->emitSource(indent);
    }
    std::cout << '\n';
  }

  if (!typeDecls.empty())
  {
    for (auto&& typeDecl : typeDecls)
    {
      typeDecl->emitSource(indent);
    }
    std::cout << '\n';
  }

  if (!varDecls.empty())
  {
    for (auto&& varDecl : varDecls)
    {
      varDecl->emitSource(indent);
    }
    std::cout << '\n';
  }

  if (!block.empty())
  {
    for (auto&& statment : block)
    {
      statment->emitSource(indent);
    }
  }
}

void BodyNode::emit() {}
