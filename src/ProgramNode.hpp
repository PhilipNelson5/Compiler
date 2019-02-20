#ifndef PROGRAM_NODE_HPP
#define PROGRAM_NODE_HPP

#include "ConstantDeclarationNode.hpp"
#include "ListNode.hpp"
#include "Node.hpp"
#include "RegisterPool.hpp"
#include "StatementNode.hpp"
#include "TypeDeclarationNode.hpp"
#include "VariableDeclarationNode.hpp"

#include <memory>
#include <vector>


class ProgramNode : public Node
{
public:
  ProgramNode(ListNode<ConstantDeclarationNode>*& cds,
              ListNode<TypeDeclarationNode>*& tds,
              ListNode<VariableDeclarationNode>*& vds,
              ListNode<StatementNode>*& mb);
  virtual void emitSource(std::string indent) override;
  virtual RegisterPool::Register emit() override;

private:
  std::vector<std::shared_ptr<ConstantDeclarationNode>> constantDecls;
  std::vector<std::shared_ptr<TypeDeclarationNode>> typeDecls;
  std::vector<std::shared_ptr<VariableDeclarationNode>> varDecls;
  // std::vector<std::shared_ptr<NodeList> procedureAndFunctionDecls;
  std::vector<std::shared_ptr<StatementNode>> mainBlock;
};

#endif
