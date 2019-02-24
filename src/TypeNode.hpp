#ifndef TYPE_NODE_HPP
#define TYPE_NODE_HPP

#include "Node.hpp"

class TypeNode : public Node
{
public:
  TypeNode(std::string ident)
    : ident(ident)
  {}
  const std::string ident;
};

#endif
