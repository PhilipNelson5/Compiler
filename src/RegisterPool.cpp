#include "RegisterPool.hpp"

#include "log/easylogging++.h" // for Writer, CERROR, LOG

#include <algorithm> // for min
#include <stdlib.h>  // for exit, EXIT_FAILURE

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

const std::vector<int> Register::getRegistersInUse()
{
  if (pool.size() == 18) return {};

  const static std::vector fullPool{
    8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

  if (pool.size() == 0) return fullPool;

  std::sort(std::begin(pool), std::end(pool));

  std::vector<int> inUse;
  inUse.reserve(fullPool.size() - pool.size());

  std::set_difference(std::begin(fullPool),
                      std::end(fullPool),
                      std::begin(pool),
                      std::end(pool),
                      std::back_inserter(inUse));

  return inUse;
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

