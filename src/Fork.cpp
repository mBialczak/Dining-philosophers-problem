#include "Fork.hpp"

Fork::Fork(Logger& logger, int id)
    : logger_(logger),
      currently_used(false),
      id_(id)
{ }

int Fork::id() const
{
    return id_;
}