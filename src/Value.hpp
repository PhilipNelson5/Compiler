#ifndef VALUE_HPP
#define VALUE_HPP

#include "RegisterPool.hpp"
#include "log/easylogging++.h"

#include <iostream>
#include <utility>
#include <variant>

struct Value
{
  enum RegisterIs
  {
    VALUE,
    ADDRESS
  };

  using intPair = std::pair<int, int>;
  using Register = RegisterPool::Register;
  using registerPair = std::pair<Register, RegisterIs>;

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

  Value(RegisterPool::Register&& reg, RegisterIs regIs = RegisterIs::VALUE)
    : value(std::make_pair(std::move(reg), regIs))
  {}

  bool isLvalue() const { return std::holds_alternative<intPair>(value); }

  bool isRegister() const
  {
    return std::holds_alternative<registerPair>(value);
  }

  bool holdsAddress() const
  {
    if (!isRegister())
    {
      LOG(ERROR) << "Not a register";
      exit(EXIT_FAILURE);
    }
    return std::get<registerPair>(value).second == RegisterIs::ADDRESS;
  }

  Register getRegister()
  {
    if (!isRegister())
    {
      LOG(ERROR) << "Not a register";
      exit(EXIT_FAILURE);
    }
    return std::move(std::get<registerPair>(value).first);
  }

  std::string getLocation() const
  {
    if (!isLvalue())
    {
      LOG(ERROR) << "No memory associated with this value";
      exit(EXIT_FAILURE);
    }
    auto p = std::get<intPair>(value);
    return std::to_string(p.first) + "($" + std::to_string(p.second) + ")";
  }

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
      return std::string(1, character);
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
    else if (std::holds_alternative<intPair>(value))
    {
      RegisterPool::Register result;
      std::cout << "lw " << result << ", " << std::get<intPair>(value).first
                << "($" << std::get<intPair>(value).second << ")\n";
      return result;
    }
    else if (std::holds_alternative<registerPair>(value))
    {
      if (std::get<registerPair>(value).second == RegisterIs::ADDRESS)
      {
        std::cout << "lw " << std::get<registerPair>(value).first << ", "
                  << "0(" << std::get<registerPair>(value).first << ")" << '\n';
      }
      return std::move(std::get<registerPair>(value).first);
    }
    else if (std::holds_alternative<std::monostate>(value))
    {
      throw "Uninitialized Value";
    }
    throw "Uninitialized Value";
  }

  std::variant<std::monostate,                  // uninitialized state
               int,                             // const int value
               char,                            // const char value
               std::string,                     // const string label
               std::pair<int, int>,             // offset, memory location
               std::pair<Register, RegisterIs>> // Register, Register is value
                                                // or address
    value;
};

#endif
