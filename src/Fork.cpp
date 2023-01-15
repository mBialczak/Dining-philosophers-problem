#include "Fork.hpp"

Fork::Fork(Logger& logger, int id)
    : logger_(logger),
      id_(id)
{ }

int Fork::id() const
{
    return id_;
}

std::mutex& Fork::getMtx()
{
    return forkMtx_;
}