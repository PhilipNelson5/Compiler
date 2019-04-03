#ifndef PROCEDURE_CALL_NODE_HPP
#define PROCEDURE_CALL_NODE_HPP

#include "ExpressionNode.hpp"
#include "ListNode.hpp"
#include "Node.hpp"
#include "StatementNode.hpp"

#include <memory>
#include <vector>

class ProcedureCallNode : public StatementNode
{
public:
  ProcedureCallNode(char* id, ListNode<ExpressionNode>*& args)
    : id(id)
    , args(ListNode<ExpressionNode>::makeVector(args))
  {}

  virtual void emitSource(std::string indent) override;
  virtual void emit() override;

  const std::string id;
  const std::vector<std::shared_ptr<ExpressionNode>> args;
};

#endif
