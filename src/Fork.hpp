#pragma once

#include "Logger.hpp"

#include <memory>
#include <mutex>

class Fork
{
  public:
    Fork(Logger& logger, int id);
    std::mutex& getMtx();
    int id() const;

  private:
    Logger& logger_;
    mutable std::mutex forkMtx_;
    const int id_;
};