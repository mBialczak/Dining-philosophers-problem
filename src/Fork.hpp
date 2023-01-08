#pragma once

#include "Logger.hpp"

#include <memory>
#include <shared_mutex>   // //TODO: VERIFY if shared or ordinary
class Logger;

class Fork
{
  public:
    // explicit Fork(const std::shared_ptr<Logger>& logger);   // TODO: VERIFY
    explicit Fork(Logger& logger);
    // Fork(Fork&&) = default;   // TODO: REMOVE
    // void useFork();   // TODO:

  private:
    // std::shared_ptr<Logger> logger_;   // TODO: VERIFY
    Logger& logger_;
    bool currently_used;
    mutable std::shared_mutex forkMtx_;
};