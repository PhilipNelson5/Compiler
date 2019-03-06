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
  Value()
    : value()
  {}

  Value(int int_value)
    : value(int_value)
  {}

  Value(char char_value)
    : value(char_value)
  {}

  Value(std::string label)
    : value(label)
  {}

  Value(int offset, int memoryLocation)
    : value(std::make_pair(offset, memoryLocation))
  {}

  Value(RegisterPool::Register&& reg)
    : value(std::move(reg))
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
    if (std::holds_alternative<int>(value))
    {
      RegisterPool::Register result;
      std::cout << "li " << result << ", " << std::get<int>(value) << '\n';
      return result;
    }
    else if (std::holds_alternative<char>(value))
    {
      RegisterPool::Register result;
      std::cout << "li " << result << ", '" << toString(std::get<char>(value))
                << '\'' << '\n';
      return result;
    }
    else if (std::holds_alternative<std::string>(value))
    {
      RegisterPool::Register result;
      std::cout << "la " << result << ", " << std::get<std::string>(value)
                << '\n';
      return result;
    }
    else if (std::holds_alternative<pair>(value))
    {
      RegisterPool::Register result;
      std::cout << "lw " << result << ", " << std::get<pair>(value).first
                << "($" << std::get<pair>(value).second << ")\n";
      return result;
    }
    else if (std::holds_alternative<Register>(value))
    {
      return std::move(std::get<Register>(value));
    }
    else if (std::holds_alternative<std::monostate>(value))
    {
      throw "Initialized Value";
    }
    throw "Initialized Value";
  }

  std::variant<std::monostate,      // uninitialized state
               int,                 // const int value
               char,                // const char value
               std::string,         // const string label
               std::pair<int, int>, // offset, memory location
               Register>            // Register
    value;
};

#endif
