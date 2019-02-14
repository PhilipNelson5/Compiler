#ifndef NODE_HPP
#define NODE_HPP

#include "RegisterPool.hpp"

#include <memory>

class Node
{
public:
  virtual void emitSource(std::string indent) = 0;
  virtual ~Node(){};
  virtual RegisterPool::Register emit() = 0;
};

#endif
