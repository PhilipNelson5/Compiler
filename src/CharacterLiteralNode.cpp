#include "CharacterLiteralNode.hpp"
#include "log/easylogging++.h"

#include "Type.hpp"

#include <iostream>
#include <string>

CharacterLiteralNode::CharacterLiteralNode(char character)
  : LiteralNode(CharacterType::get())
  , character(character)
{
  LOG(DEBUG) << "NEW CHARACTER NODE";
}

void CharacterLiteralNode::emitSource(std::string indent)
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

RegisterPool::Register CharacterLiteralNode::emit()
{
  RegisterPool::Register result;
  std::cout << "li " << result << ", ";
  emitSource("");
  std::cout << std::endl;
  return result;
}
