#ifndef READ_STATEMENT_NODE_HPP
#define READ_STATEMENT_NODE_HPP

#include "LvalueNode.hpp"
#include "ListNode.hpp"
#include "StatementNode.hpp"

#include <memory>
#include <vector>

class ReadStatementNode : StatementNode
{
public:
  ReadStatementNode(ListNode<LvalueNode>*& lVals);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::vector<std::shared_ptr<LvalueNode>> lValues;
};

#endif
