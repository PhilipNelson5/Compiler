#include "SubscriptOperatorNode.hpp"

std::shared_ptr<Type> getArrayType(LvalueNode* lValue)
{
  if (ArrayType* array = dynamic_cast<ArrayType*>(lValue->type.get()))
  {
    return array->elementType;
  }

  LOG(ERROR) << lValue->getId()
             << " is not an array type, can not use subscript operator[]";
  exit(EXIT_FAILURE);
}

SubscriptOperatorNode::SubscriptOperatorNode(LvalueNode* lValue,
                                             ExpressionNode* expr)
  : LvalueNode(getArrayType(lValue))
  , lValue(std::shared_ptr<LvalueNode>(lValue))
  , expr(std::shared_ptr<ExpressionNode>(expr))
{}

void SubscriptOperatorNode::emitSource(std::string indent)
{
  std::cout << indent << '[';
  expr->emitSource("");
  std::cout << ']';
}

Value SubscriptOperatorNode::emit()
{
  throw "SubscriptOperatorNode::emit() not implemented";
}
