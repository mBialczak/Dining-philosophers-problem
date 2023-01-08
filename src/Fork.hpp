#pragma once

#include "Logger.hpp"

#include <memory>
#include <shared_mutex>   // //TODO: VERIFY if shared or ordinary
class Logger;

class Fork
{
  public:
    explicit Fork(Logger& logger);
    // void useFork();   // TODO:

  private:
    Logger& logger_;
    bool currently_used;
    mutable std::shared_mutex forkMtx_;
};