#ifndef PROCEDURE_DECLARATION_NODE_HPP
#define PROCEDURE_DECLARATION_NODE_HPP

#include "BodyNode.hpp"
#include "FormalParameter.hpp"
#include "ListNode.hpp"
#include "Node.hpp"
#include "ProcedureOrFunctionDeclarationNode.hpp"

#include <memory>
#include <vector>

class ProcedureDeclarationNode : public ProcedureOrFunctionDeclarationNode
{
public:
  ProcedureDeclarationNode(char* id, ListNode<FormalParameter>*& parameters, BodyNode*& body)
    : id(id)
    , parameters(ListNode<FormalParameter>::makeVector(parameters))
    , body(body)
  {}

  virtual void emitSource(std::string indent) override;
  virtual void emit() override;

  const std::string id;
  const std::vector<std::shared_ptr<FormalParameter>> parameters;
  const std::shared_ptr<BodyNode> body;
};

#endif
