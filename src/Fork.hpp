#pragma once

#include "Logger.hpp"

#include <memory>
#include <shared_mutex>   // //TODO: VERIFY if shared or ordinary

class Fork
{
  public:
    explicit Fork(Logger& logger, int id);
    void useFork();   // TODO: //TODO: VERIFY const
    std::shared_mutex& getMtx(); //TODO: VERIFY
    int id() const;

  private:
    Logger& logger_;
    bool currently_used; //TODO: VERIFY
    mutable std::shared_mutex forkMtx_;
    const int id_;
};