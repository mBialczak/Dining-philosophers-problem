#include "PhilosophyMeeting.hpp"

#include "Fork.hpp"
#include "Logger.hpp"
#include "Philosopher.hpp"

PhilosophyMeeting::PhilosophyMeeting(std::ostream& streamToLog, int tableSize, int mealsToServe)
    : logger_(std::make_unique<Logger>(streamToLog)),
      tableSize_(tableSize),
      meals_(mealsToServe)
{
    createForks();

    // philosophers_.reserve(tableSize_);
    // threads_.reserve(tableSize_);
}

void PhilosophyMeeting::createForks()
{
    forks_.reserve(tableSize_);
    for (auto i = 0; i < tableSize_; i++) {
        forks_.emplace_back(std::make_unique<Fork>(*logger_));
    }
}
