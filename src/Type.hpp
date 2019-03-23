#ifndef TYPE_HPP
#define TYPE_HPP

#include "../fmt/include/fmt/core.h" // for print
#include "ListNode.hpp"              // for ListNode
#include "TypeNode.hpp"              // for TypeNode
#include "log/easylogging++.h"       // for Writer, CERROR, LOG

#include <iostream> // for operator<<, cout, ostream, basi...
#include <iterator> // for end
#include <map>      // for map, map<>::iterator, _Rb_tree_...
#include <memory>   // for shared_ptr, make_shared, allocator
#include <numeric>  // for accumulate
#include <stdlib.h> // for exit, EXIT_FAILURE
#include <string>   // for string, operator<<, operator+
#include <utility>  // for pair, make_pair
#include <vector>   // for vector

//------------------------------------------------------------------------------
// Type
//------------------------------------------------------------------------------
class Type
{
public:
  virtual int size() const { return 4; };
  virtual std::string name() const = 0;
  virtual ~Type() = default;
  virtual void emitSource(std::string indent) const = 0;
};

//------------------------------------------------------------------------------
// Integer Type
//------------------------------------------------------------------------------
class IntegerType : public Type
{
public:
  std::string name() const override { return "integer"; }

  static std::shared_ptr<Type> get()
  {
    if (!pInt) pInt = std::make_shared<IntegerType>();
    return pInt;
  }

  virtual void emitSource(std::string indent) const override
  {
    (void)indent;
    std::cout << name();
  }

private:
  static std::shared_ptr<Type> pInt;
};

//------------------------------------------------------------------------------
// Character Type
//------------------------------------------------------------------------------
class CharacterType : public Type
{
public:
  std::string name() const override { return "character"; }

  static std::shared_ptr<Type> get()
  {
    if (!pChar) pChar = std::make_shared<CharacterType>();
    return pChar;
  }

  virtual void emitSource(std::string indent) const override
  {
    (void)indent;
    std::cout << name();
  }

private:
  static std::shared_ptr<Type> pChar;
};

//------------------------------------------------------------------------------
// Boolean Type
//------------------------------------------------------------------------------
class BooleanType : public Type
{
public:
  std::string name() const override { return "boolean"; }

  static std::shared_ptr<Type> get()
  {
    if (!pBool) pBool = std::make_shared<BooleanType>();
    return pBool;
  }

  virtual void emitSource(std::string indent) const override
  {
    (void)indent;
    std::cout << name();
  }

private:
  static std::shared_ptr<Type> pBool;
};

//------------------------------------------------------------------------------
// String Type
//------------------------------------------------------------------------------
class StringType : public Type
{
public:
  int size() const override { return 0; }

  virtual std::string name() const override { return "string"; }

  static std::shared_ptr<Type> get()
  {
    if (!pStr) pStr = std::make_shared<StringType>();
    return pStr;
  }

  virtual void emitSource(std::string indent) const override
  {
    (void)indent;
    std::cout << name();
  }

private:
  static std::shared_ptr<Type> pStr;
};

//------------------------------------------------------------------------------
// Array Type
//------------------------------------------------------------------------------
class ArrayType : public Type
{
public:
  ArrayType(int lb, int ub, std::shared_ptr<Type> elementType, std::shared_ptr<Type> indexType)
    : lb(lb)
    , ub(ub)
    , indexType(indexType)
    , elementType(elementType)
  {}

  virtual std::string name() const override { return "array"; }

  virtual void emitSource(std::string indent) const override
  {
    (void)indent;
    fmt::print("array[{}:{}] of ", lb, ub);
    elementType->emitSource(indent + "  ");
  }

  const int lb, ub;
  const std::shared_ptr<Type> indexType;
  const std::shared_ptr<Type> elementType;

  virtual int size() const override { return (ub - lb + 1) * elementType->size(); }
};

//------------------------------------------------------------------------------
// Record Type
//------------------------------------------------------------------------------
struct Field
{
  Field(ListNode<std::string>*& idList, TypeNode* typeNode)
    : ids(ListNode<std::string>::makeDerefVector(idList))
    , type(typeNode->type)
  {}
  const std::vector<std::string> ids;
  const std::shared_ptr<Type> type;
};

class RecordType : public Type
{
public:
  RecordType(ListNode<Field>*& fields)
  {
    int offset = 0;
    auto vecFields = ListNode<Field>::makeVector(fields);
    for (auto&& f : vecFields)
    {
      for (auto&& id : f->ids)
      {
        table.emplace(id, std::make_pair(offset, f->type));
        offset += f->type->size();
      }
    }
  }

  virtual std::string name() const override { return "record"; }

  virtual void emitSource(std::string indent) const override
  {
    std::cout << "record" << '\n';
    for (auto&& r : table)
    {
      std::cout << indent << r.first << " : ";
      r.second.second->emitSource(indent + "  ");
      std::cout << ";\n";
    }
    std::cout << std::string(indent.length() - 2, ' ') << "end";
  }

  std::map<std::string, std::pair<int, std::shared_ptr<Type>>> table;

  std::pair<int, std::shared_ptr<Type>> lookupId(std::string id)
  {
    auto found = table.find(id);
    if (found == std::end(table))
    {
      LOG(ERROR) << id << "does not exist in record";
      exit(EXIT_FAILURE);
    }
    return found->second;
  }

  virtual int size() const override
  {
    return std::accumulate(table.begin(), table.end(), 0, [](int sum, auto e) {
      return sum + e.second.second->size();
    });
  }
};

#endif
