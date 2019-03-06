#include "StopStatementNode.hpp"

#include <iostream>

StopStatementNode::StopStatementNode() {}

void StopStatementNode::emitSource(std::string indent)
{
  std::cout << indent << "stop;" << std::endl;
}

Value StopStatementNode::emit()
{
  std::cout << "li $v0, 10"
            << " # load exit instruction" << std::endl;
  std::cout << "syscall" << std::endl;

  return {};
}
