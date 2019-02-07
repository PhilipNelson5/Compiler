#ifndef NODE_HPP
#define NODE_HPP

#include "RegisterPool.hpp"

class Node
{
public:
  virtual void emmitSource() = 0;
  virtual RegisterPool::Register emmit() = 0;
};

#endif
