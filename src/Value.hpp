#ifndef VALUE_HPP
#define VALUE_HPP

#include "RegisterPool.hpp"

#include <iostream>

struct Value
{
  enum Type
  {
    CONST_INT,
    CONST_CHAR,
    CONST_STRING,
    LVAL,
    REGISTER,
    UNINIT
  };

  Value()
    : reg(0)
    , type(Type::UNINIT)
  {}

  Value(int int_value)
    : int_value(int_value)
    , reg(0)
    , type(Type::CONST_INT)
  {}

  Value(char char_value)
    : char_value(char_value)
    , reg(0)
    , type(Type::CONST_CHAR)
  {}

  Value(std::string label)
    : label(label)
    , reg(0)
    , type(Type::CONST_STRING)
  {}

  Value(int offset, int memoryLocation)
    : offset(offset)
    , memoryLocation(memoryLocation)
    , reg(0)
    , type(Type::LVAL)
  {}

  Value(RegisterPool::Register&& reg)
    : reg(std::move(reg))
    , type(Type::REGISTER)
  {}

  std::string toString(char character) const
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
      return &character;
    }
  }

  RegisterPool::Register getTheeIntoARegister()
  {
    switch (type)
    {
    case Type::CONST_INT:
    {
      RegisterPool::Register result;
      std::cout << "li " << result << ", " << int_value << '\n';
      return result;
    }
    case Type::CONST_CHAR:
    {
      RegisterPool::Register result;
      std::cout << "li " << result << ", '" << toString(char_value) << '\''
                << '\n';
      return result;
    }
    case Type::CONST_STRING:
    {
      RegisterPool::Register result;
      std::cout << "la " << result << ", " << label << '\n';
      return result;
    }
    case Type::LVAL:
    {
      RegisterPool::Register result;
      std::cout << "lw " << result << ", " << offset << "($" << memoryLocation
                << ")\n";
      return result;
    }
    case Type::REGISTER:
    {
      return std::move(reg);
    }
    case Type::UNINIT:
    {
      throw "Initialized Value";
    }
    }
    throw "Initialized Value";
  }

  int int_value;
  char char_value;
  std::string label;
  int offset;
  int memoryLocation;
  RegisterPool::Register reg;
  Type type;
};

#endif
