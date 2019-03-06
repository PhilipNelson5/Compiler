#ifndef READ_STATEMENT_NODE_HPP
#define READ_STATEMENT_NODE_HPP

#include <memory>             // for shared_ptr
#include <string>             // for string
#include <vector>             // for vector
#include "StatementNode.hpp"  // for StatementNode
#include "Value.hpp"          // for Value
class LvalueNode;
template <typename T> class ListNode;  // lines 14-15

class ReadStatementNode : public StatementNode
{
public:
  ReadStatementNode(ListNode<LvalueNode>*& lVals);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

private:
  std::vector<std::shared_ptr<LvalueNode>> identifiers;
};

#endif
