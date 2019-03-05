#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "AddNode.hpp"
#include "ConstantDeclarationNode.hpp"
#include "BooleanLiteralNode.hpp"
#include "CharacterLiteralNode.hpp"
#include "DivideNode.hpp"
#include "EqualExpressionNode.hpp"
#include "ExpressionNode.hpp"
#include "IntegerLiteralNode.hpp"
#include "LvalueNode.hpp"
#include "ModuloNode.hpp"
#include "MultiplyNode.hpp"
#include "NotEqualExpressionNode.hpp"
#include "StringLiteralNode.hpp"
#include "SubtractNode.hpp"
#include "SymbolTable.hpp"
#include "log/easylogging++.h"

#include <iostream>

template<typename NodeType, typename LiteralType, typename F>
ExpressionNode* makeNode(ExpressionNode* e1, ExpressionNode* e2, F f)
{
  LiteralType* lit1 = nullptr;
  LiteralType* lit2 = nullptr;

  // ----------------------------------------
  // Find expression 1 as literal or constant
  // ----------------------------------------
  if (e1->isLiteral())
  {
    lit1 = dynamic_cast<LiteralType*>(e1);
  }
  else if (e1->isConstant())
  {
    auto c1 = dynamic_cast<LvalueNode*>(e1);
    lit1 = dynamic_cast<LiteralType*>(symbol_table.lookupConst(c1->id).get());
  }
  else
  {
    return new NodeType(e1, e2);
  }

  // ----------------------------------------
  // Find expression 2 as literal or constant
  // ----------------------------------------
  if (e2->isLiteral())
  {
    lit2 = dynamic_cast<LiteralType*>(e2);
  }
  else if (e2->isConstant())
  {
    auto c2 = dynamic_cast<LvalueNode*>(e2);
    lit2 = dynamic_cast<LiteralType*>(symbol_table.lookupConst(c2->id).get());
  }
  else
  {
    return new NodeType(e1, e2);
  }

  // ---------------------------------
  // If both are found, constant fold;
  // ---------------------------------
  if (lit1 && lit2)
  {
    return new LiteralType(f(lit1->value, lit2->value));
  }
  else
  {
    return new NodeType(e1, e2);
  }
}

ExpressionNode* makeAddNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<AddNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 + v2; });
}

ExpressionNode* makeSubtractNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<SubtractNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 - v2; });
}

ExpressionNode* makeMultiplyNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<MultiplyNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 * v2; });
}

ExpressionNode* makeDivideNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<DivideNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 / v2; });
}

ExpressionNode* makeModuloNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<ModuloNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 % v2; });
}

ExpressionNode* makeNotEqualNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<NotEqualExpressionNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 != v2; });
}

ExpressionNode* makeEqualNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<EqualExpressionNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 == v2; });
}

ExpressionNode* makeLiteralNode(LvalueNode* e)
{
  auto const_info = symbol_table.lookupConst(e->id);
  if (const_info != nullptr)
  {
    if (const_info->type == IntegerType::get())
    {
      return new IntegerLiteralNode(
        dynamic_cast<IntegerLiteralNode*>(const_info.get())->value);
    }
    if (const_info->type == BooleanType::get())
    {
      return new BooleanLiteralNode(
        dynamic_cast<BooleanLiteralNode*>(const_info.get())->value);
    }
    if (const_info->type == CharacterType::get())
    {
      return new CharacterLiteralNode(
        dynamic_cast<CharacterLiteralNode*>(const_info.get())->character);
    }
    if (const_info->type == StringType::get())
    {
      return new StringLiteralNode(
        dynamic_cast<StringLiteralNode*>(const_info.get())->string);
    }
    LOG(ERROR) << e->id << " : " << e->type->name() << " can not be turned into a literal";
    exit(EXIT_FAILURE);
  }
  LOG(ERROR) << e->id << "is not defined in the const symbol table";
  exit(EXIT_FAILURE);
}

ConstantDeclarationNode* makeConstantDeclarationNode(std::string id, ExpressionNode* e)
{
  // if ( Expression is an Lvalue )
  if(LvalueNode* plval = dynamic_cast<LvalueNode*>(e))
  {
    return new ConstantDeclarationNode(id, makeLiteralNode(plval));
  }
  // if ( Expression is a Literal )
  else if(LiteralNode* plit = dynamic_cast<LiteralNode*>(e))
  {
    return new ConstantDeclarationNode(id, plit);
  }
  else
  {
    LOG(ERROR) << "Non-Const expression in Constant Declaration";
    exit(EXIT_FAILURE);
  }
}

ExpressionNode* makeLvalueNode(std::string id)
{
  auto const_info = symbol_table.lookupConst(id);
  if (const_info != nullptr)
  {
    if (const_info->type == IntegerType::get())
    {
      return new IntegerLiteralNode(
        dynamic_cast<IntegerLiteralNode*>(const_info.get())->value);
    }
    if (const_info->type == BooleanType::get())
    {
      return new BooleanLiteralNode(
        dynamic_cast<BooleanLiteralNode*>(const_info.get())->value);
    }
    if (const_info->type == CharacterType::get())
    {
      return new CharacterLiteralNode(
        dynamic_cast<CharacterLiteralNode*>(const_info.get())->character);
    }
    if (const_info->type == StringType::get())
    {
      return new StringLiteralNode(
        dynamic_cast<StringLiteralNode*>(const_info.get())->string);
    }
  }

  return new LvalueNode(id);
}

#endif
