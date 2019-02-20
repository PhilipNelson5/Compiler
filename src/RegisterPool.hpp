#ifndef REGISTER_POOL_HPP
#define REGISTER_POOL_HPP

#include <memory>
#include <ostream>
#include <string>
#include <vector>

class RegisterPool
{
public:
  class Register;

private:
  static std::unique_ptr<RegisterPool> instance;

  std::vector<RegisterPool::Register> pool;

public:
  class Register
  {
  public:
    // move constructor
    Register(Register&& old);

    // destructor
    ~Register();

    // register name getter
    std::string toString() const { return name; }

    // constructor
    Register(std::string name);

  private:
    // deleted copy constructor
    Register(const Register& reg) = delete;

    // deleted assignment operator
    Register& operator=(Register&& reg) = delete;

    // Register name
    std::string name;

  }; // class Register

  RegisterPool();

public:
  static RegisterPool* getInstance();

  Register getRegister();

}; // class RegisterPool

std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r);

#endif
