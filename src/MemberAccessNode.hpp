#ifndef MEMBER_ACCESS_NODE_HPP
#define MEMBER_ACCESS_NODE_HPP

#include "LvalueNode.hpp" // for LvalueNode
#include "Value.hpp"      // for Value

#include <memory> // for shared_ptr
#include <string> // for string

class MemberAccessNode : public LvalueNode
{
public:
  MemberAccessNode(LvalueNode* lValue, std::string id);
  virtual void emitSource(std::string indent) override;
  virtual Value emit() override;

  std::shared_ptr<LvalueNode> lValue;
  std::string id;
};

#endif
