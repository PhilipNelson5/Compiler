#ifndef PROGRAM_NODE_HPP
#define PROGRAM_NODE_HPP

#include "ListNode.hpp"
#include "Node.hpp"
#include "RegisterPool.hpp"
#include "StatementNode.hpp"
#include "VariableDeclarationNode.hpp"

#include <memory>
#include <vector>


class ProgramNode : public Node
{
public:
  ProgramNode(ListNode<VariableDeclarationNode>*& vds,
              ListNode<StatementNode>*& mb);
  virtual void emmitSource() override;
  virtual RegisterPool::Register emmit() override;

private:
  // std::vector<std::shared_ptr<NodeList> constantDecls;
  // std::vector<std::shared_ptr<NodeList> typeDecls;
  std::vector<std::shared_ptr<VariableDeclarationNode>> varDecls;
  // std::vector<std::shared_ptr<NodeList> procedureAndFunctionDecls;
  std::vector<std::shared_ptr<StatementNode>> mainBlock;
};

#endif
