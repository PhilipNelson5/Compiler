#include "ReadStatementNode.hpp"

#include "ListNode.hpp"        // for ListNode
#include "LvalueNode.hpp"      // for LvalueNode
#include "RegisterPool.hpp"    // for operator<<
#include "Type.hpp"            // for CharacterType, IntegerType, Type
#include "log/easylogging++.h" // for Writer, CERROR, LOG

#include <ext/alloc_traits.h> // for __alloc_traits<>::value_type
#include <iostream>           // for operator<<, basic_ostream, cout, ostream
#include <stdlib.h>           // for exit, EXIT_FAILURE

ReadStatementNode::ReadStatementNode(ListNode<LvalueNode>*& identifiers)
  : identifiers(ListNode<LvalueNode>::makeVector(identifiers))
{}

void ReadStatementNode::emitSource(std::string indent)
{
  std::cout << indent << "read(";
  for (auto i = 0u; i < identifiers.size() - 1; ++i)
  {
    identifiers[i]->emitSource("");
    std::cout << ", ";
  }
  identifiers.back()->emitSource("");
  std::cout << ");" << std::endl;
}

Value ReadStatementNode::emit()
{
  std::cout << "\n# ";
  emitSource("");

  for (auto&& identifier : identifiers)
  {
    auto v_id = identifier->emit();
    if (!v_id.isLvalue())
    {
      LOG(ERROR) << identifier->getId() << " is not an Lvalue";
      exit(EXIT_FAILURE);
    }

    if (identifier->type == IntegerType::get())
    {
      std::cout << "li $v0, 5"
                << " # load read integer instruction" << '\n';
    }
    else if (identifier->type == CharacterType::get())
    {
      std::cout << "li $v0, 12"
                << " # load read character instruction" << '\n';
    }
    else
    {
      LOG(ERROR) << "type " << identifier->type->name()
                 << " can not be read into";
      exit(EXIT_FAILURE);
    }

    std::cout << "syscall" << '\n';
    std::cout << "sw $v0, " << v_id.getLocation();
    std::cout << " # " << identifier->getId() << " = input" << '\n' << '\n';
  }

  return {};
}

