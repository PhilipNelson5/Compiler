#include "CharacterConstantNode.hpp"

#include <iostream>
#include <string>

CharacterConstantNode::CharacterConstantNode(char character)
  : character(character)
{}

void CharacterConstantNode::emitSource(std::string indent)
{
  std::cout << indent << "'";
  switch (character)
  {
  case '\n':
    std::cout << "\\n";
    break;
  case '\r':
      std::cout << "\\r";
      break;
  case '\b':
      std::cout << "\\b";
      break;
  case '\t':
      std::cout << "\\t";
      break;
  case '\f':
      std::cout << "\\f";
      break;
  default:
      std::cout << character;
  }
  std::cout << "'";
}

RegisterPool::Register CharacterConstantNode::emit()
{
  throw "not implemented";
}
