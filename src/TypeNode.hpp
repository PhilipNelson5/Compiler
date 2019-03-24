#ifndef TYPE_NODE_HPP
#define TYPE_NODE_HPP

#include "SymbolTable.hpp"

#include <memory> // for shared_ptr

class Type;

class TypeNode
{
public:
  TypeNode(std::string id)
    : id(id)
    , type(nullptr)
  {}

  TypeNode(std::shared_ptr<Type> type)
    : id()
    , type(type)
  {}

  const std::shared_ptr<Type> getType()
  {
    if (type == nullptr)
    {
      type = symbol_table.lookupType(id);
    }
    return type;
  }

private:
  std::string id;
  std::shared_ptr<Type> type;
};
#endif
