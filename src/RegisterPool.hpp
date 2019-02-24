#ifndef REGISTER_POOL_HPP
#define REGISTER_POOL_HPP

#include <memory>
#include <ostream>
#include <string>
#include <vector>


namespace RegisterPool
{
class Register
{
public:
  // constructor
  Register();

  // move constructor
  Register(Register&& old);

  // move assignment operator
  Register& operator=(Register&& reg) = default;

  // destructor
  ~Register();

  // register name getter
  std::string toString() const { return "$" + std::to_string(name); }

private:
  // deleted copy constructor
  Register(const Register& reg) = delete;

  // deleted assignment operator
  Register& operator=(const Register& reg) = delete;

  // initialize the pool
  void init();

  // Register name
  int name;

  // pool of registers
  static std::vector<int> pool;

}; // class Register
} // namespace RegisterPool

std::ostream& operator<<(std::ostream& o, RegisterPool::Register const& r);

#endif
