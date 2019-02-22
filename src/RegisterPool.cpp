#include "RegisterPool.hpp"

namespace RegisterPool
{
std::vector<std::string> Register::pool;

Register::Register(Register&& old)
  : name{old.name}
{
  old.name = "$INVALID";
}

Register::Register()
{
  init();
  name = pool.back();
  pool.pop_back();
}

Register::~Register()
{
  if (name != "$INVALID")
  {
    pool.emplace_back(name);
  }
}

void Register::init()
{
  static bool initialized = false;

  if (initialized)
    return;
  else
    initialized = true;

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
} // namespace RegisterPool

std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r)
{
  o << r.toString();
  return o;
}

