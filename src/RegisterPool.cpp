#include "RegisterPool.hpp"

namespace RegisterPool
{
std::vector<int> Register::pool;

Register::Register(Register&& old)
  : name{old.name}
{
  old.name = -1;
}

Register::Register()
{
  init();
  name = pool.back();
  pool.pop_back();
}

Register::~Register()
{
  if (name != -1)
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
  pool.emplace_back(8);
  pool.emplace_back(9);
  pool.emplace_back(10);
  pool.emplace_back(11);
  pool.emplace_back(12);
  pool.emplace_back(13);
  pool.emplace_back(14);
  pool.emplace_back(15);
  pool.emplace_back(16);
  pool.emplace_back(17);
  pool.emplace_back(18);
  pool.emplace_back(19);
  pool.emplace_back(20);
  pool.emplace_back(21);
  pool.emplace_back(22);
  pool.emplace_back(23);
  pool.emplace_back(24);
  pool.emplace_back(25);
}
} // namespace RegisterPool

std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r)
{
  o << r.toString();
  return o;
}

