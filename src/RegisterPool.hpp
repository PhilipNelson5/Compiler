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
    friend RegisterPool;

  public:
    // move constructor
    //Register(Register&& old);

    // destructor
    ~Register();

    // register name getter
    std::string str() const;

  private:
    // constructor
    Register(std::string name);

    // deleted copy constructor
    //Register(const Register& reg) = delete;

    // deleted assignment operator
    //Register& operator=(Register&& reg) = delete;

    // Register name
    std::string name;

  }; // Class Register

  friend Register;

public:
  RegisterPool();

  Register getRegister();

private:
  static std::vector<RegisterPool::Register> pool;
};

#endif
