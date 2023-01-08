#include "PhilosophyMeeting.hpp"

#include "Fork.hpp"
#include "Logger.hpp"
#include "Philosopher.hpp"

PhilosophyMeeting::PhilosophyMeeting(std::ostream& streamToLog, int tableSize, int mealsToServe)
    // : logger_(std::make_shared<Logger>(streamToLog)), // TODO: REMOVE
    : logger_(std::make_unique<Logger>(streamToLog)),
      tableSize_(tableSize),
      meals_(mealsToServe)
//   forks_(std::vector<Fork>(tableSize, Fork { logger }))tododr?

{
    createForks();
    // Fork fork(logger_);
    // auto fork = std::make_shared<Fork>(logger_);
    // Logger& logging(logger_);
    // Fork { logging };
    // Fork fork { logger_.get() };
    // forks_.emplace_back(std::move(fork));
    // forks_.emplace_back(logger_);

    // forks2_.emplace_back(std::make_unique<Fork>(logger_));
    // for (auto i = 0; i < tableSize_; i++) {
    //     forks_.emplace_back(std::make_shared<Fork>(logger_));
    // }
    // Fork fk(logger_);
    // forks_.push_back(std::move(fk));
    // forks_.emplace_back(logger_);

    // forks_.emplace_back(logger_);
    // Fork someFork { logger_ };
    // forks_.emplace_back(std::move(someFork));

    // philosophers_.reserve(tableSize_);
    // threads_.reserve(tableSize_);
}
// TODO: VERIFY
//  void PhilosophyMeeting::createForks()
//  {
//      for (auto i = 0; i < tableSize_; i++) {
//          forks_.emplace_back(std::make_shared<Fork>(logger_));
//      }
//  }
//  void PhilosophyMeeting::createForks()
//  {
//      for (auto i = 0; i < tableSize_; i++) {
//          forks_.emplace_back(std::make_unique<Fork>(logger_));
//      }
//  }
void PhilosophyMeeting::createForks()
{
    forks_.reserve(tableSize_);
    for (auto i = 0; i < tableSize_; i++) {
        forks_.emplace_back(std::make_unique<Fork>(*logger_));
    }
}
// void PhilosophyMeeting::createForks()
// {
//     Fork fk(logger_);

//     forks_.emplace_back(std::move(fk));
//     // Fork fk(*logger_);
//     // forks_.push_back(std::move(fk));
//     // forks_.emplace_back(std::move(fk));

//     // for (auto i = 0; i < tableSize_; i++) {
//     //     forks_.emplace_back(*logger_);
//     // }
// }