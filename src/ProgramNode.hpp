#ifndef PROGRAM_NODE_HPP
#define PROGRAM_NODE_HPP

#include "Node.hpp"

#include <memory>
#include <vector>

using NodeList = std::vector<std::unique_ptr<Node>>;
using Node_p = std::unique_ptr<Node>;

class ProgramNode : public Node
{
public:
  ProgramNode()
    : constantDecls{nullptr}
  {}

private:
  NodeList constantDecls;
  NodeList typeDecls;
  NodeList varDecls;
  NodeList procedureAndFunctionDecls;
};

#endif
