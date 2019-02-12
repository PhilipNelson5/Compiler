#ifndef WRITE_STATEMENT_NODE_HPP
#define WRITE_STATEMENT_NODE_HPP

#include "ExpressionNode.hpp"
#include "ListNode.hpp"
#include "Node.hpp"

#include <memory>
#include <vector>

class WriteStatementNode : public Node
{
public:
  WriteStatementNode(ListNode<ExpressionNode>*& exprList);
  virtual void emmitSource() override;
  virtual RegisterPool::Register emmit() override;

private:
  std::vector<std::shared_ptr<ExpressionNode>> expressionList;
};

#endif
