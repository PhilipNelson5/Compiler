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

bool CharacterLiteralNode::isLiteral()
{
  return true;
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
  (void)indent;
  std::cout << "'" << toString() << "'";
}

Value CharacterLiteralNode::emit()
{
  return character;
}
