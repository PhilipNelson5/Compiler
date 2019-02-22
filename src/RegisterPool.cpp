#include "RegisterPool.hpp"

// ----------------------------------------------------------------------------
// Register Pool
// ----------------------------------------------------------------------------
std::unique_ptr<RegisterPool> RegisterPool::instance = nullptr;

RegisterPool::RegisterPool():pool()
{
  pool.reserve(18);
  pool.emplace_back(std::string("$s0"));
  pool.emplace_back(std::string("$s1"));
  pool.emplace_back(std::string("$s2"));
  pool.emplace_back(std::string("$s3"));
  pool.emplace_back(std::string("$s4"));
  pool.emplace_back(std::string("$s5"));
  pool.emplace_back(std::string("$s6"));
  pool.emplace_back(std::string("$s7"));
  pool.emplace_back(std::string("$t0"));
  pool.emplace_back(std::string("$t1"));
  pool.emplace_back(std::string("$t2"));
  pool.emplace_back(std::string("$t3"));
  pool.emplace_back(std::string("$t4"));
  pool.emplace_back(std::string("$t5"));
  pool.emplace_back(std::string("$t6"));
  pool.emplace_back(std::string("$t7"));
  pool.emplace_back(std::string("$t8"));
  pool.emplace_back(std::string("$t9"));
}

RegisterPool* RegisterPool::getInstance()
{
  if(instance == nullptr)
  {
    instance = std::make_unique<RegisterPool>();
  }
  return instance.get();
}

RegisterPool::Register RegisterPool::getRegister()
{
  auto reg = Register(getInstance()->pool.back());
  getInstance()->pool.pop_back();
  return reg;
}

// ----------------------------------------------------------------------------
// Register
// ----------------------------------------------------------------------------

RegisterPool::Register::Register(Register&& old)
  : name{old.name}
{
  old.name = "$INVALID";
}

RegisterPool::Register::Register(std::string name)
  : name{name}
{}

RegisterPool::Register::~Register()
{
  if(name!="$INVALID")
  // instance->pool.push_back(std::move(*this));
  getInstance()->pool.emplace_back(name);
}

std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r)
{
  o << r.toString();
  return o;
}

