#include "RegisterPool.hpp"

#include "log/easylogging++.h"

#include <cmath>

namespace RegisterPool
{
std::vector<int> Register::pool;
size_t Register::low;

Register::Register(Register&& old)
  : name{old.name}
  , valid(true)
{
  old.name = -1;
  old.valid = false;
}

Register::Register()
  : valid(true)
{
  init();
  if (pool.size() == 0)
  {
    LOG(ERROR) << "No more registers available";
    exit(EXIT_FAILURE);
  }
  name = pool.back();
  pool.pop_back();
  low = std::min(low, pool.size());
}

Register::~Register()
{
  if (valid)
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

  low = pool.size();
}
} // namespace RegisterPool

std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r)
{
  o << r.toString();
  return o;
}

