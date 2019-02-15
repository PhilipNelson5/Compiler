#ifndef STOP_STATEMENT_NODE_HPP
#define STOP_STATEMENT_NODE_HPP

#include "StatementNode.hpp"

class StopStatementNode : public StatementNode
{
public:
  StopStatementNode();
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;
};

#endif
