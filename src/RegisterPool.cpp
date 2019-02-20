#include "RegisterPool.hpp"

// ----------------------------------------------------------------------------
// Register Pool
// ----------------------------------------------------------------------------
std::unique_ptr<RegisterPool> RegisterPool::instance
  = std::make_unique<RegisterPool>();

RegisterPool::RegisterPool()
{
  pool.emplace_back("$s0");
  pool.emplace_back("$s1");
  pool.emplace_back("$s2");
  pool.emplace_back("$s3");
  pool.emplace_back("$s4");
  pool.emplace_back("$s5");
  pool.emplace_back("$s6");
  pool.emplace_back("$s7");
  pool.emplace_back("$t0");
  pool.emplace_back("$t1");
  pool.emplace_back("$t2");
  pool.emplace_back("$t3");
  pool.emplace_back("$t4");
  pool.emplace_back("$t5");
  pool.emplace_back("$t6");
  pool.emplace_back("$t7");
  pool.emplace_back("$t8");
  pool.emplace_back("$t9");
}

RegisterPool* RegisterPool::getInstance()
{
  return instance.get();
}

RegisterPool::Register RegisterPool::getRegister()
{
  auto reg = std::move(instance->pool.back());
  instance->pool.pop_back();
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
  // instance->pool.push_back(std::move(*this));
  instance->pool.emplace_back(name);
}

std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r)
{
  o << r.toString();
  return o;
}

