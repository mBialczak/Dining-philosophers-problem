#include "Fork.hpp"

Fork::Fork(int id)
    : id_(id)
{ }

int Fork::id() const
{
    return id_;
}

std::mutex& Fork::getMtx()
{
    return forkMtx_;
}