#include "StopStatementNode.hpp"

#include <iostream>

StopStatementNode::StopStatementNode() {}

void StopStatementNode::emitSource(std::string indent)
{
  std::cout << indent << "stop;" << std::endl;
}

RegisterPool::Register StopStatementNode::emit()
{
  throw "not implemented StopStatementNode";
}
