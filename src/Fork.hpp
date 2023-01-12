#pragma once

#include "Logger.hpp"

#include <memory>
#include <shared_mutex>   // //TODO: VERIFY if shared or ordinary

class Fork
{
  public:
    explicit Fork(Logger& logger, int id);
    std::shared_mutex& getMtx();
    int id() const;

  private:
    Logger& logger_;
    mutable std::shared_mutex forkMtx_;
    const int id_;
};