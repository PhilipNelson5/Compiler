#include "SubscriptOperatorNode.hpp"

#include <sstream>
struct cout_redirect
{
  cout_redirect(std::streambuf* new_buffer)
    : old(std::cout.rdbuf(new_buffer))
  {}

  ~cout_redirect() { std::cout.rdbuf(old); }

private:
  std::streambuf* old;
};

std::string SubscriptOperatorNode::getId()
{
  std::stringstream s_expr;
  { // remporarily redirect stdout to the s_expr stringstream
    cout_redirect redirect(s_expr.rdbuf());
    expr->emitSource("");
  }
  return lValue->getId() + "[" + s_expr.str() + "]";
}

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
  (void)indent;
  lValue->emitSource(indent);
  std::cout << '[';
  expr->emitSource("");
  std::cout << ']';
}

Value SubscriptOperatorNode::emit()
{
  if (ArrayType* array = dynamic_cast<ArrayType*>(lValue->type.get()))
  {
    auto v_lval = lValue->emit();

    std::cout << "# ";
    emitSource("");
    std::cout << '\n';

    auto r_index = expr->emit().getTheeIntoARegister();
    std::cout << "addi " << r_index << ", " << r_index << ", " << -array->lb
              << " # adjust the index ( indx - lb )\n";

    RegisterPool::Register elementSize;
    std::cout << "li " << elementSize << ", " << array->elementType->size()
              << " # get array element size\n";

    std::cout << "mult " << r_index << ", " << elementSize << '\n';
    std::cout << "mflo " << r_index
              << " # multiply the number of elements by the element size\n";

    if (v_lval.isLvalue())
    {
      auto [offset, memoryLocation]
        = std::get<std::pair<int, int>>(v_lval.value);

      std::cout << "addi " << r_index << ", " << r_index << ", " << offset
                << " # add the offset to the index\n";

      std::cout << "add " << r_index << ", " << r_index << ", $"
                << memoryLocation
                << " # add the memory location to the index\n";

      return {std::move(r_index), Value::RegisterIs::ADDRESS};
    }
    if (v_lval.isRegister())
    {
      auto r_lval = v_lval.getRegister();

      std::cout << "add " << r_index << ", " << r_index << ", " << r_lval
                << " # add the index to the memory address\n";

      return {std::move(r_index), Value::RegisterIs::ADDRESS};
    }
    LOG(ERROR) << lValue->getId() << " is not an Lvalue, no memory associated";
    exit(EXIT_FAILURE);
  }
  else
  {
    LOG(ERROR) << lValue->getId() << " is not an array type";
    exit(EXIT_FAILURE);
  }
}
