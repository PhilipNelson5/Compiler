#ifndef VALUE_HPP
#define VALUE_HPP

#include "RegisterPool.hpp"

#include <iostream>
#include <utility>
#include <variant>

using pair = std::pair<int, int>;
using Register = RegisterPool::Register;

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
    : type(Type::UNINIT)
  {}

  Value(int int_value)
    : value(int_value)
    , type(Type::CONST_INT)
  {}

  Value(char char_value)
    : value(char_value)
    , type(Type::CONST_CHAR)
  {}

  Value(std::string label)
    : value(label)
    , type(Type::CONST_STRING)
  {}

  Value(int offset, int memoryLocation)
    : value(std::make_pair(offset, memoryLocation))
    , type(Type::LVAL)
  {}

  Value(RegisterPool::Register&& reg)
    : value(std::move(reg))
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
      std::cout << "li " << result << ", " << std::get<int>(value) << '\n';
      return result;
    }
    case Type::CONST_CHAR:
    {
      RegisterPool::Register result;
      std::cout << "li " << result << ", '" << toString(std::get<char>(value))
                << '\'' << '\n';
      return result;
    }
    case Type::CONST_STRING:
    {
      RegisterPool::Register result;
      std::cout << "la " << result << ", " << std::get<std::string>(value)
                << '\n';
      return result;
    }
    case Type::LVAL:
    {
      RegisterPool::Register result;
      std::cout << "lw " << result << ", " << std::get<pair>(value).first
                << "($" << std::get<pair>(value).second << ")\n";
      return result;
    }
    case Type::REGISTER:
    {
      return std::move(std::get<Register>(value));
    }
    case Type::UNINIT:
    {
      throw "Initialized Value";
    }
    }
    throw "Initialized Value";
  }

  /*
    int int_value;
    char char_value;
    std::string label;
    std::pair<int offset, int memoryLocation>
    RegisterPool::Register reg;
  */
  std::variant<int, char, std::string, std::pair<int, int>, Register> value;
  Type type;
};

#endif
