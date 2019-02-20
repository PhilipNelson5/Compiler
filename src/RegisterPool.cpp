#include "RegisterPool.hpp"

RegisterPool RegisterPool::RP = RegisterPool();

std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r)
{
  o << r.str();
  return o;
}
