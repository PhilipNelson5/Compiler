#include "MemberAccessNode.hpp"

#include "Type.hpp"            // for RecordType
#include "log/easylogging++.h" // for Writer, CERROR, LOG

#include <iostream> // for operator<<, basic_ostream, cout, ostream
#include <iterator> // for end
#include <map>      // for _Rb_tree_iterator, map
#include <stdlib.h> // for exit, EXIT_FAILURE
#include <utility>  // for pair

std::shared_ptr<Type> lookupId(LvalueNode* lValue, std::string id)
{
  if (RecordType* pRecord = dynamic_cast<RecordType*>(lValue->type.get()))
  {
    auto member = pRecord->table.find(id);
    if (member != std::end(pRecord->table))
    {
      return member->second.second;
    }
    else
    {
      LOG(ERROR) << "Member " << id << " does not exist";
      exit(EXIT_FAILURE);
    }
  }
  LOG(ERROR) << "Can not use member access on non record types";
  exit(EXIT_FAILURE);
}

MemberAccessNode::MemberAccessNode(LvalueNode* lValue, std::string id)
  : LvalueNode(lookupId(lValue, id))
  , lValue(std::shared_ptr<LvalueNode>(lValue))
  , id(id)
{}

void MemberAccessNode::emitSource(std::string indent)
{
  std::cout << indent << '.' << id;
}

Value MemberAccessNode::emit()
{
  throw "MemberAccessNode::emit not implemented";
}
