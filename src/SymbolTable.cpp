#include "SymbolTable.hpp"

#include "../fmt/include/fmt/core.h" // for format
#include "BooleanLiteralNode.hpp"    // for BooleanLiteralNode
#include "LiteralNode.hpp"           // for LiteralNode
#include "Type.hpp"                  // for Type, BooleanType, CharacterType
#include "log/easylogging++.h"       // for Writer, LOG, CDEBUG, CERROR

#include <iostream> // for cout
#include <stdlib.h> // for exit, EXIT_FAILURE
#include <utility>  // for pair

SymbolTable symbol_table;

SymbolTable::SymbolTable()
{
  // Enter Predefined Scope
  scopes.emplace_back();
  auto itPredefines = scopes.rbegin();
  itPredefines->constants.emplace(std::string("true"), new BooleanLiteralNode(1));
  itPredefines->constants.emplace(std::string("false"), new BooleanLiteralNode(0));

  itPredefines->types.emplace(std::string("integer"), IntegerType::get());
  itPredefines->types.emplace(std::string("char"), CharacterType::get());
  itPredefines->types.emplace(std::string("boolean"), BooleanType::get());
  itPredefines->types.emplace(std::string("string"), StringType::get());

  // Enter Global Scope
  enter_scope();
}

std::shared_ptr<Type> SymbolTable::getType(std::string id)
{
  auto lval_info = lookupLval(id);
  if (lval_info != nullptr)
  {
    return lval_info->type;
  }

  auto const_info = lookupConst(id);
  if (const_info != nullptr)
  {
    return const_info->type;
  }

  LOG(ERROR) << id << " is not defined";
  exit(EXIT_FAILURE);
}

std::shared_ptr<Type> SymbolTable::lookupType(std::string id) const
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

const std::string SymbolTable::lookupString(std::string str)
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

const std::string SymbolTable::newLabel(std::string name)
{
  static unsigned n = 0u;
  return fmt::format("{}_{}", name, n++);
}

std::shared_ptr<Variable> SymbolTable::lookupLval(std::string id) const
{
  LOG(DEBUG) << "lookupLval(" << id << ")";
  for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
  {
    auto foundVar = scope->variables.find(id);
    if (foundVar != scope->variables.end())
    {
      return foundVar->second;
    }
  }
  LOG(DEBUG) << id << " not defined as variable";
  return nullptr;
}

std::shared_ptr<LiteralNode> SymbolTable::lookupConst(std::string id) const
{
  LOG(DEBUG) << "lookupConst(" << id << ")";
  for (auto scope = scopes.rbegin(); scope != scopes.rend(); ++scope)
  {
    auto foundConst = scope->constants.find(id);
    if (foundConst != scope->constants.end())
    {
      return foundConst->second;
    }
  }
  LOG(DEBUG) << id << " not defined as constant";
  return nullptr;
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
    LOG(ERROR) << id << " is already defined as a variable in the current scope\n";
    exit(EXIT_FAILURE);
  }

  if (foundConst != top->constants.end())
  {
    LOG(ERROR) << id << " is already defined as a constant in the current scope\n";
    exit(EXIT_FAILURE);
  }

  // set the offset and increment by the type's size;
  auto var = std::make_shared<Variable>(id, type, globalPointer, globalOffset);
  globalOffset += var->type->size();

  // Insert in top level scope
  top->variables.emplace(id, var);
  LOG(DEBUG) << fmt::format(
    "{}:{} stored in variable symbol table at scope {}", id, type->name(), scopes.size() - 1);
}

void SymbolTable::storeConst(std::string id, std::shared_ptr<LiteralNode> literal)
{
  // Find on top level - error if already defined
  auto top = scopes.rbegin();
  auto foundVar = top->variables.find(id);
  auto foundConst = top->constants.find(id);

  if (foundVar != top->variables.end())
  {
    LOG(ERROR) << id << " is already defined as a variable in the current scope\n";
    exit(EXIT_FAILURE);
  }

  if (foundConst != top->constants.end())
  {
    LOG(ERROR) << id << " is already defined as a constant in the current scope\n";
    exit(EXIT_FAILURE);
  }

  // Insert in top level scope
  top->constants.emplace(id, literal);

  LOG(DEBUG) << fmt::format("{}:{} stored in constant symbol table at scope {}",
                            id,
                            literal->type->name(),
                            scopes.size() - 1);
}

void SymbolTable::storeType(std::string id, std::shared_ptr<Type> type)
{
  // Find on top level - error if already defined
  auto top = scopes.rbegin();
  auto foundType = top->types.find(id);

  if (foundType != top->types.end())
  {
    LOG(ERROR) << id << " is already defined as a type in the current scope\n";
    exit(EXIT_FAILURE);
  }

  // Insert in top level scope
  top->types.emplace(id, type);
  LOG(DEBUG) << fmt::format(
    "{}:{} stored in type symbol table at scope {}", id, type->name(), scopes.size() - 1);
}

void SymbolTable::printStrings() const
{
  for (auto cur = strings.begin(); cur != strings.end(); ++cur)
  {
    std::cout << cur->second << ": .asciiz " << cur->first << '\n';
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
