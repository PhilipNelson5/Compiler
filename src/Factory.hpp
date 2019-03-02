#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "AddNode.hpp"
#include "BooleanLiteralNode.hpp"
#include "DivideNode.hpp"
#include "EqualExpressionNode.hpp"
#include "ExpressionNode.hpp"
#include "IntegerLiteralNode.hpp"
#include "ModuloNode.hpp"
#include "MultiplyNode.hpp"
#include "NotEqualExpressionNode.hpp"
#include "SubtractNode.hpp"

#include <iostream>

template<typename NodeType, typename LiteralType, typename F>
ExpressionNode* makeNode(ExpressionNode* e1, ExpressionNode* e2, F f)
{
  if (e1->isLiteral() && e2->isLiteral())
  {
    return new LiteralType(f(dynamic_cast<IntegerLiteralNode*>(e1)->value,
                             dynamic_cast<IntegerLiteralNode*>(e2)->value));
  }
  else
    return new NodeType(e1, e2);
}

ExpressionNode* makeAddNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<AddNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 + v2; });

  if (e1->isLiteral() && e2->isLiteral())
  {
    return new IntegerLiteralNode(
      dynamic_cast<IntegerLiteralNode*>(e1)->value
      + dynamic_cast<IntegerLiteralNode*>(e2)->value);
  }
  else
    return new AddNode(e1, e2);
}

ExpressionNode* makeSubtractNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<SubtractNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 - v2; });

  if (e1->isLiteral() && e2->isLiteral())
  {
    return new IntegerLiteralNode(
      dynamic_cast<IntegerLiteralNode*>(e1)->value
      - dynamic_cast<IntegerLiteralNode*>(e2)->value);
  }
  else
    return new SubtractNode(e1, e2);
}

ExpressionNode* makeMultiplyNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<MultiplyNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 * v2; });

  if (e1->isLiteral() && e2->isLiteral())
  {
    return new IntegerLiteralNode(
      dynamic_cast<IntegerLiteralNode*>(e1)->value
      * dynamic_cast<IntegerLiteralNode*>(e2)->value);
  }
  else
    return new MultiplyNode(e1, e2);
}

ExpressionNode* makeDivideNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<DivideNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 / v2; });

  if (e1->isLiteral() && e2->isLiteral())
  {
    return new IntegerLiteralNode(
      dynamic_cast<IntegerLiteralNode*>(e1)->value
      / dynamic_cast<IntegerLiteralNode*>(e2)->value);
  }
  else
    return new DivideNode(e1, e2);
}

ExpressionNode* makeModuloNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<ModuloNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 % v2; });

  if (e1->isLiteral() && e2->isLiteral())
  {
    return new IntegerLiteralNode(
      dynamic_cast<IntegerLiteralNode*>(e1)->value
      % dynamic_cast<IntegerLiteralNode*>(e2)->value);
  }
  else
    return new ModuloNode(e1, e2);
}

ExpressionNode* makeNotEqualNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<NotEqualExpressionNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 != v2; });

  if (e1->isLiteral() && e2->isLiteral())
  {
    return new IntegerLiteralNode(
      dynamic_cast<IntegerLiteralNode*>(e1)->value
      != dynamic_cast<IntegerLiteralNode*>(e2)->value);
  }
  else
    return new NotEqualExpressionNode(e1, e2);
}

ExpressionNode* makeEqualNode(ExpressionNode* e1, ExpressionNode* e2)
{
  return makeNode<EqualExpressionNode, IntegerLiteralNode>(
    e1, e2, [](auto v1, auto v2) { return v1 == v2; });

  if (e1->isLiteral() && e2->isLiteral())
  {
    return new IntegerLiteralNode(
      dynamic_cast<IntegerLiteralNode*>(e1)->value
      == dynamic_cast<IntegerLiteralNode*>(e2)->value);
  }
  else
    return new NotEqualExpressionNode(e1, e2);
}

#endif
