#include "CharacterLiteralNode.hpp"

#include "Type.hpp"
#include "log/easylogging++.h"

#include <iostream>
#include <string>

CharacterLiteralNode::CharacterLiteralNode(char character)
  : LiteralNode(CharacterType::get())
  , character(character)
{
  LOG(DEBUG) << "NEW CHARACTER NODE";
}

std::string CharacterLiteralNode::toString() const
{
  switch (character)
  {
  case '\n':
    return "\\n";
  case '\r':
    return "\\r";
  case '\b':
    return "\\b";
  case '\t':
    return "\\t";
  case '\f':
    return "\\f";
  default:
    return {1, character};
  }
}

void CharacterLiteralNode::emitSource(std::string indent)
{
  std::cout << indent << "'" << toString() << "'";
}

Value CharacterLiteralNode::emit()
{
  return character;
}
