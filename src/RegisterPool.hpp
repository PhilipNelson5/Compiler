#ifndef REGISTER_POOL_HPP
#define REGISTER_POOL_HPP

#include <ostream>
#include <string>
#include <vector>

class RegisterPool
{
public:
  class Register
  {
    friend class RegisterPool;

  public:
    // move constructor
    Register(Register&& old)
      : name{old.str()}
    {
      old.name = "";
    }

    // destructor
    //~Register() { RegisterPool::getPool().pool.push_back(std::move(*this)); }
    ~Register() { RegisterPool::rp.pool.push_back(std::move(*this)); }

    // register name getter
    std::string str() const { return name; };

  private:
    // constructor
    Register(std::string name)
      : name{name}
    {}

    // deleted copy constructor
    Register(const Register& reg) = delete;

    // deleted assignment operator
    Register& operator=(Register&& reg) = delete;

    // Register name
    std::string name;

  }; // Class Register

  friend class Register;

public:
  static Register getRegister()
  {
    auto reg = std::move(rp.pool.back());
    rp.pool.pop_back();
    return reg;
  }

  static RegisterPool& getPool() { return rp; }

private:
  RegisterPool()
    : pool{Register("$s0"),
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
           Register("$t9")}
  {}

  static RegisterPool rp;

  std::vector<Register> pool;
};

std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r)
{
  o << r.str();
  return o;
}


#endif
