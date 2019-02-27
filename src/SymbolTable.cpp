#include "SymbolTable.hpp"

#include "BooleanConstantNode.hpp"
#include "IntegerConstantNode.hpp"
#include "log/easylogging++.h"

#include <iostream>

SymbolTable symbol_table;

SymbolTable::SymbolTable()
{
  // Predefines
  scopes.emplace_back();
  auto itPredefines = scopes.rbegin();
  itPredefines->constants.emplace(std::string("true"),
                                  new BooleanConstantNode(1));
  itPredefines->constants.emplace(std::string("false"),
                                  new BooleanConstantNode(0));

  itPredefines->types.emplace(std::string("integer"), IntegerType::get());
  itPredefines->types.emplace(std::string("char"), CharacterType::get());
  itPredefines->types.emplace(std::string("boolean"), BooleanType::get());
  itPredefines->types.emplace(std::string("string"), StringType::get());

  // Enter Global Scope
  enter_scope();
}

std::shared_ptr<Type> SymbolTable::lookupType(std::string id)
{
  LOG(DEBUG) << "lookupType(" << id << ")";
  for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
  {
    auto found = scope->types.find(id);
    if (found != scope->types.end())
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

Variable SymbolTable::lookupLval(std::string id)
{
  LOG(DEBUG) << "lookupLval(" << id << ")";
  for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
  {
    auto foundVar = scope->variables.find(id);
    if (foundVar != scope->variables.end())
    {
      return foundVar->second;
    }

    // auto foundConst = scope->constants.find(id);
    // if (foundConst != scope->constants.end())
    //{
    // return foundConst->second;
    //}
  }
  LOG(ERROR) << id << " not defined";
  exit(EXIT_FAILURE);
}

void SymbolTable::storeVariable(std::string id, std::shared_ptr<Type> type)
{
  static int globalOffset = 0;

  // Find on top level - error if already defined
  auto top = scopes.rbegin();
  auto foundVar = top->variables.find(id);
  auto foundConst = top->constants.find(id);

  if (foundVar != top->variables.end())
  {
    LOG(ERROR) << id << " is already defined as a variable in the scope\n";
    exit(EXIT_FAILURE);
  }

  if (foundConst != top->constants.end())
  {
    LOG(ERROR) << id << " is already defined as a constant in the scope\n";
    exit(EXIT_FAILURE);
  }

  // set the offset and increment by the type's size;
  Variable var(id, type, globalPointer, globalOffset);
  globalOffset += var.type->size();

  // Insert in top level scope
  top->variables.emplace(id, var);
  LOG(DEBUG) << id << ":" << type->name() << " stored in symbol table at scope "
             << scopes.size() - 1;
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
  scopes.emplace_back();
}

void SymbolTable::exit_scope()
{
  scopes.pop_back();
}
