#include "RegisterPool.hpp"

// RegisterPool::Register::Register(RegisterPool::Register&& old)
//: name{old.str()}
//{
// old.name = "";
//}

RegisterPool::Register::Register(std::string name)
  : name{name}
{}

RegisterPool::Register::~Register()
{
  // RegisterPool::pool.push_back(std::move(*this));
}

std::string RegisterPool::Register::str() const
{
  return name;
}

RegisterPool::Register RegisterPool::getRegister()
{
  auto reg = std::move(pool.back());
  pool.pop_back();
  return reg;
}

RegisterPool::RegisterPool() {}

std::vector<RegisterPool::Register> RegisterPool::pool{Register("$s0"),
                                                       Register("$s1"),
                                                       Register("$s2"),
                                                       Register("$s3"),
                                                       Register("$s4"),
                                                       Register("$s5"),
                                                       Register("$s6"),
                                                       Register("$s7"),
                                                       Register("$t0"),
                                                       Register("$t1"),
                                                       Register("$t2"),
                                                       Register("$t3"),
                                                       Register("$t4"),
                                                       Register("$t5"),
                                                       Register("$t6"),
                                                       Register("$t7"),
                                                       Register("$t8"),
                                                       Register("$t9")};


// std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r)
//{
// o << r.str();
// return o;
//}

