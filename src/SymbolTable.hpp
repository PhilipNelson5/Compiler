#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "ExpressionNode.hpp"
#include "Type.hpp"

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

struct Variable
{
  std::string identifier;
  std::shared_ptr<Type> type;
  int memoryLocation;
  int offset = 0;

  Variable() = default;

  virtual ~Variable() = default;

  Variable(std::string& identifier,
           std::shared_ptr<Type> const& type,
           int memoryLocation,
           int offset = 0)
    : identifier(identifier)
    , type(type)
    , memoryLocation(memoryLocation)
    , offset(offset)
  {}

  std::string getLoc()
  {
    std::stringstream ss;
    ss << offset << "($" << memoryLocation << ")";
    return ss.str();
  }
};

struct Scope
{
  std::map<std::string, std::shared_ptr<ExpressionNode>> constants;
  std::map<std::string, std::shared_ptr<Variable>> variables;
  std::map<std::string, std::shared_ptr<Type>> types;
};

class SymbolTable
{
public:
  SymbolTable();
  std::shared_ptr<ExpressionNode> lookupConst(std::string id) const;
  std::shared_ptr<Variable> lookupLval(std::string id) const;
  std::shared_ptr<Type> lookupType(std::string id) const;
  const std::string lookupString(std::string str);
  void storeConst(std::string id, std::shared_ptr<ExpressionNode> expr);
  void storeVariable(std::string id, std::shared_ptr<Type> type);
  void storeType(std::string id, std::shared_ptr<Type> type);
  void printStrings() const;
  void enter_scope();
  void exit_scope();

private:
  std::map<std::string, std::string> strings;
  std::vector<Scope> scopes;

  static constexpr int globalPointer = 28;
};

extern SymbolTable symbol_table;

#endif
