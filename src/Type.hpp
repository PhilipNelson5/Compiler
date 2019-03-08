#ifndef TYPE_HPP
#define TYPE_HPP

#include "ListNode.hpp"
#include "TypeNode.hpp"
#include "log/easylogging++.h"

#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

//------------------------------------------------------------------------------
// Type
//------------------------------------------------------------------------------
class Type
{
public:
  virtual int size() { return 4; };
  virtual std::string name() = 0;
  virtual ~Type() = default;
  virtual void emitSource(std::string indent) = 0;
};

//------------------------------------------------------------------------------
// Integer Type
//------------------------------------------------------------------------------
class IntegerType : public Type
{
public:
  std::string name() override { return "integer"; }

  static std::shared_ptr<Type> get()
  {
    if (!pInt) pInt = std::make_shared<IntegerType>();
    return pInt;
  }

  virtual void emitSource(std::string indent) override
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
  std::string name() override { return "character"; }

  static std::shared_ptr<Type> get()
  {
    if (!pChar) pChar = std::make_shared<CharacterType>();
    return pChar;
  }

  virtual void emitSource(std::string indent) override
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
  std::string name() override { return "boolean"; }

  static std::shared_ptr<Type> get()
  {
    if (!pBool) pBool = std::make_shared<BooleanType>();
    return pBool;
  }

  virtual void emitSource(std::string indent) override
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
  int size() override { return 0; }

  virtual std::string name() override { return "string"; }

  static std::shared_ptr<Type> get()
  {
    if (!pStr) pStr = std::make_shared<StringType>();
    return pStr;
  }

  virtual void emitSource(std::string indent) override
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
  ArrayType(int lb,
            int ub,
            std::shared_ptr<Type> elementType,
            std::shared_ptr<Type> indexType)
    : lb(lb)
    , ub(ub)
    , indexType(indexType)
    , elementType(elementType)
  {}

  virtual std::string name() override { return "array"; }

  virtual void emitSource(std::string indent) override
  {
    (void)indent;
    std::cout << name();
  }

  const int lb, ub;
  const std::shared_ptr<Type> indexType;
  const std::shared_ptr<Type> elementType;

  virtual int size() override { return ub - lb + 1 * elementType->size(); }
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

  virtual std::string name() override { return "record"; }

  virtual void emitSource(std::string indent) override
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

  virtual int size() override
  {
    return std::accumulate(table.begin(), table.end(), 0, [](int sum, auto e) {
      return sum + e.second.second->size();
    });
  }
};

#endif
