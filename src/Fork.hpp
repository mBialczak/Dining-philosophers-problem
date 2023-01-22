#pragma once

#include "Logger.hpp"

#include <memory>
#include <mutex>

class Fork
{
  public:
    Fork(int id);
    std::mutex& getMtx();
    int id() const;

  private:
    mutable std::mutex forkMtx_;
    const int id_;
};