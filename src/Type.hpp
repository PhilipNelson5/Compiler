#ifndef TYPE_HPP
#define TYPE_HPP

#include <memory>
#include <string>

//------------------------------------------------------------------------------
// Type
//------------------------------------------------------------------------------
class Type
{
public:
  virtual int size() { return 4; };
  virtual std::string name() = 0;
  virtual ~Type() = default;
};

//------------------------------------------------------------------------------
// Integer Type
//------------------------------------------------------------------------------
class IntegerType : public Type
{
public:
  std::string name() override { return "integer"; }

  static std::shared_ptr<Type> get()
  {
    if (!pInt) pInt = std::make_shared<IntegerType>();
    return pInt;
  }

private:
  static std::shared_ptr<Type> pInt;
};

//------------------------------------------------------------------------------
// Character Type
//------------------------------------------------------------------------------
class CharacterType : public Type
{
public:
  std::string name() override { return "character"; }

  static std::shared_ptr<Type> get()
  {
    if (!pChar) pChar = std::make_shared<CharacterType>();
    return pChar;
  }

private:
  static std::shared_ptr<Type> pChar;
};

//------------------------------------------------------------------------------
// Boolean Type
//------------------------------------------------------------------------------
class BooleanType : public Type
{
public:
  std::string name() override { return "boolean"; }

  static std::shared_ptr<Type> get()
  {
    if (!pBool) pBool = std::make_shared<BooleanType>();
    return pBool;
  }

private:
  static std::shared_ptr<Type> pBool;
};

//------------------------------------------------------------------------------
// String Type
//------------------------------------------------------------------------------
class StringType : public Type
{
public:
  int size() override { return 0; }

  std::string name() override { return "string"; }

  static std::shared_ptr<Type> get()
  {
    if (!pStr) pStr = std::make_shared<StringType>();
    return pStr;
  }

private:
  static std::shared_ptr<Type> pStr;
};

#endif
