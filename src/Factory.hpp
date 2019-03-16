#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "AddNode.hpp"                 // for AddNode
#include "BooleanLiteralNode.hpp"      // for BooleanLiteralNode
#include "CharacterLiteralNode.hpp"    // for CharacterLiteralNode
#include "ConstantDeclarationNode.hpp" // for ConstantDeclarationNode
#include "DivideNode.hpp"              // for DivideNode
#include "EqualExpressionNode.hpp"     // for EqualExpressionNode
#include "ExpressionNode.hpp"          // for ExpressionNode
#include "IntegerLiteralNode.hpp"      // for IntegerLiteralNode
#include "LiteralNode.hpp"             // for LiteralNode
#include "LvalueNode.hpp"              // for LvalueNode
#include "ModuloNode.hpp"              // for ModuloNode
#include "MultiplyNode.hpp"            // for MultiplyNode
#include "NotEqualExpressionNode.hpp"  // for NotEqualExpressionNode
#include "StringLiteralNode.hpp"       // for StringLiteralNode
#include "SubtractNode.hpp"            // for SubtractNode
#include "SymbolTable.hpp"             // for SymbolTable, symbol_table
#include "Type.hpp"                    // for ArrayType, IntegerType, Chara...
#include "UnaryMinusNode.hpp"
#include "log/easylogging++.h" // for Writer, CERROR, LOG

#include <memory>   // for shared_ptr, operator==, make_...
#include <stdlib.h> // for exit, EXIT_FAILURE
#include <string>   // for string

template<typename LiteralType>
LiteralType* literalize(ExpressionNode* e)
{
  if (e->isLiteral())
  {
    return dynamic_cast<LiteralType*>(e);
  }
  else if (e->isConstant())
  {
    auto c1 = dynamic_cast<LvalueNode*>(e);
    return dynamic_cast<LiteralType*>(
      symbol_table.lookupConst(c1->getId()).get());
  }
  return nullptr;
}

template<typename NodeType, typename LiteralType, typename F>
ExpressionNode* makeBinaryExpressionNode(ExpressionNode* e1,
                                         ExpressionNode* e2,
                                         F f)
{
  // ----------------------------------------
  // Find expression 1 as literal or constant
  // ----------------------------------------
  LiteralType* lit1 = literalize<LiteralType>(e1);


  // ----------------------------------------
  // Find expression 2 as literal or constant
  // ----------------------------------------
  LiteralType* lit2 = literalize<LiteralType>(e2);

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

template<typename NodeType, typename LiteralType, typename F>
ExpressionNode* makeUnaryExpresisonNode(ExpressionNode* e, F f)
{
  // ----------------------------------------
  // Find expression as literal or constant
  // ----------------------------------------
  LiteralType* lit = literalize<LiteralType>(e);

  if (lit)
  {
    return new LiteralType(f(lit->value));
  }
  else
  {
    return new NodeType(e);
  }
}

ExpressionNode* makeUnaryMinusNode(ExpressionNode* e)
{
  return makeUnaryExpresisonNode<UnaryMinusNode, IntegerLiteralNode>(
    e, [](auto v) { return -v; });
}

ExpressionNode* makeAddNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeBinaryExpressionNode<AddNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 + v2; });
}

ExpressionNode* makeSubtractNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeBinaryExpressionNode<SubtractNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 - v2; });
}

ExpressionNode* makeMultiplyNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeBinaryExpressionNode<MultiplyNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 * v2; });
}

ExpressionNode* makeDivideNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeBinaryExpressionNode<DivideNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 / v2; });
}

ExpressionNode* makeModuloNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeBinaryExpressionNode<ModuloNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 % v2; });
}

ExpressionNode* makeNotEqualNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeBinaryExpressionNode<NotEqualExpressionNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 != v2; });
}

ExpressionNode* makeEqualNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeBinaryExpressionNode<EqualExpressionNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 == v2; });
}

ExpressionNode* makeLiteralNode(LvalueNode* e)
{
  auto const_info = symbol_table.lookupConst(e->getId());
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
    LOG(ERROR) << e->getId() << " : " << e->type->name()
               << " can not be turned into a literal";
    exit(EXIT_FAILURE);
  }
  LOG(ERROR) << e->getId() << "is not defined in the const symbol table";
  exit(EXIT_FAILURE);
}

ConstantDeclarationNode* makeConstantDeclarationNode(std::string id,
                                                     ExpressionNode* e)
{
  // if ( Expression is an IdentifierNode )
  if (LvalueNode* plval = dynamic_cast<LvalueNode*>(e))
  {
    return new ConstantDeclarationNode(id, makeLiteralNode(plval));
  }
  // if ( Expression is a Literal )
  else if (LiteralNode* plit = dynamic_cast<LiteralNode*>(e))
  {
    return new ConstantDeclarationNode(id, plit);
  }
  else
  {
    LOG(ERROR) << "Non-Const expression in Constant Declaration";
    exit(EXIT_FAILURE);
  }
}

std::shared_ptr<ArrayType> makeArray(ExpressionNode* e1,
                                     ExpressionNode* e2,
                                     TypeNode* type)
{
  if (e1->type != e2->type)
  {
    LOG(ERROR) << "array bounds must have the same type";
    exit(EXIT_FAILURE);
  }
  if (e1->type == IntegerType::get())
  {
    IntegerLiteralNode* i1 = literalize<IntegerLiteralNode>(e1);
    IntegerLiteralNode* i2 = literalize<IntegerLiteralNode>(e2);
    return std::make_shared<ArrayType>(
      i1->value, i2->value, type->type, IntegerType::get());
  }
  if (e1->type == CharacterType::get())
  {
    CharacterLiteralNode* c1 = literalize<CharacterLiteralNode>(e1);
    CharacterLiteralNode* c2 = literalize<CharacterLiteralNode>(e2);
    return std::make_shared<ArrayType>(
      c1->character, c2->character, type->type, IntegerType::get());
  }

  LOG(ERROR) << "array bounds must be integer or character type";
  exit(EXIT_FAILURE);
}

#if 0
ExpressionNode* makeIdentifierNode(std::string id)
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

  return new IdentifierNode(id);
}
#endif

#endif
