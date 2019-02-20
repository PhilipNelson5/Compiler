#ifndef REGISTER_POOL_HPP
#define REGISTER_POOL_HPP

#include <ostream>
#include <string>
#include <vector>

class RegisterPool
{
public:
  class Register;
  friend Register;

private:
  std::vector<RegisterPool::Register> pool;

  RegisterPool() { initPool(); }

public:
  static RegisterPool RP;

public:
  class Register
  {
    friend void initPool();

  public:
    // move constructor
    Register(Register&& old)
      : name{old.str()}
    {
      old.name = "$INVALID";
    }

    // destructor
    ~Register() { RegisterPool::RP.pool.push_back(std::move(*this)); }

    // register name getter
    std::string str() const { return name; }

    // constructor
    Register(std::string name)
      : name{name}
    {}

  private:
    // deleted copy constructor
    Register(const Register& reg) = delete;

    // deleted assignment operator
    Register& operator=(Register&& reg) = delete;

    // Register name
    std::string name;

  }; // class Register

public:
  Register getRegister()
  {
    auto reg = std::move(RP.pool.back());
    RP.pool.pop_back();
    return reg;
  }

  void initPool()
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

}; // class RegisterPool

#endif
