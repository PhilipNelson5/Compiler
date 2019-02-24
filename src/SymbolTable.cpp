#include "SymbolTable.hpp"

#include "log/easylogging++.h"

#include <iostream>

SymbolTable symbol_table;

SymbolTable::SymbolTable()
{
  variables.emplace_back();
  types.emplace_back();
  auto top = types.rbegin();
  top->emplace(std::string("integer"), IntegerType::get());
  top->emplace(std::string("char"), CharacterType::get());
  top->emplace(std::string("string"), StringType::get());
}

std::shared_ptr<Type> SymbolTable::lookupType(std::string id)
{
  for (auto cur = types.rbegin(); cur != types.rend(); cur++)
  {
    auto found = cur->find(id);
    if (found != cur->end())
    {
      return found->second;
    }
  }
  LOG(ERROR) << id << " not defined";
  exit(EXIT_FAILURE);
}

std::string SymbolTable::lookupString(std::string str)
{
  static int num = 0;
  const static std::string name = "string";
  auto found = strings.find(str);

  if (found == strings.end())
  {
    auto newLabel = name + std::to_string(num++);
    strings.emplace(str, newLabel);
    return newLabel;
  }

  return found->second;
}

Variable SymbolTable::lookupVariable(std::string id)
{
  for (auto cur = variables.rbegin(); cur != variables.rend(); cur++)
  {
    auto found = cur->find(id);
    if (found != cur->end())
    {
      return found->second;
    }
  }
  LOG(ERROR) << id << " not defined";
  exit(EXIT_FAILURE);
}

void SymbolTable::storeVariable(std::string id, std::shared_ptr<Type> type)
{
  static int globalOffset = 0;

  // Find on top level - error if already defined
  auto top = variables.rbegin();
  auto found = top->find(id);
  if (found != top->end())
  {
    LOG(ERROR) << id << " is already defined in the scope\n";
    exit(EXIT_FAILURE);
  }

  // set the offset and increment by the type's size;
  Variable var(id, type, globalPointer, globalOffset);
  globalOffset += var.type->size();

  // Insert in top level
  top->emplace(id, var);
  LOG(DEBUG) << id << ":" << type->name() << " stored in symbol table";
}

void SymbolTable::printStrings()
{
  for (auto cur = strings.begin(); cur != strings.end(); ++cur)
  {
    std::cout << cur->second << ": .asciiz " << cur->first << std::endl;
  }
}

void SymbolTable::enter_scope()
{
  variables.emplace_back();
}

void SymbolTable::exit_scope()
{
  variables.pop_back();
}
