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

void Fork::useFork()   // TODO: //TODO: VERIFY const
{
    // TODO: VERIFY
    std::lock_guard forkLock(forkMtx_);
    logger_ << "Using fork " << std::to_string(id_) << "\n";   //<< std::endl;
}

std::shared_mutex& Fork::getMtx()   // TODO: VERIFY
{
    return forkMtx_;
}