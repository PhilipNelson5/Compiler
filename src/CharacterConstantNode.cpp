#include "CharacterConstantNode.hpp"

#include <iostream>
#include <string>

CharacterConstantNode::CharacterConstantNode(char character)
  : character(character)
{}

void CharacterConstantNode::emitSource(std::string indent)
{
  std::cout << indent << "'" << character << "'";
}

RegisterPool::Register CharacterConstantNode::emit()
{
  throw "not implemented";
}
