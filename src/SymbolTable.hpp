#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "Type.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

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

class SymbolTable
{
public:
  SymbolTable();
  Variable lookupVariable(std::string id);
  std::shared_ptr<Type> lookupType(std::string id);
  void storeVariable(std::string id, std::shared_ptr<Type> type);
  void enter_scope();
  void exit_scope();

private:
  std::vector<std::map<std::string, Variable>> variables;
  std::vector<std::map<std::string, std::shared_ptr<Type>>> types;

  static constexpr int globalPointer = 28;
};

extern SymbolTable symbol_table;

#endif
