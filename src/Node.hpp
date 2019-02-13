#ifndef NODE_HPP
#define NODE_HPP

#include "RegisterPool.hpp"

#include <memory>

class Node
{
public:
  virtual void emmitSource(std::string indent) = 0;
  virtual ~Node(){};
  virtual RegisterPool::Register emmit() = 0;
};

#endif
