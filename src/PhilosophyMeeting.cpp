#include "PhilosophyMeeting.hpp"

#include "Logger.hpp"

#include <sstream>

PhilosophyMeeting::PhilosophyMeeting(std::ostream& streamToLog, int tableSize, int mealsToServe)
    : logger_(std::make_unique<Logger>(streamToLog)),
      tableSize_(tableSize),
      meals_(mealsToServe)
{
    createForks();
    createPhilosophers();
    threads_.reserve(tableSize_);
    describeTableArrangement();
}

void PhilosophyMeeting::createForks()
{
    forks_.reserve(tableSize_);
    for (auto i = 0; i < tableSize_; i++) {
        forks_.emplace_back(std::make_unique<Fork>(*logger_, i));
    }
}

void PhilosophyMeeting::createPhilosophers()
{
    philosophers_.reserve(tableSize_);

    createFirstPhilosopher();
    createMiddlePhilosophers();
    createLastPhilosopher();
}

void PhilosophyMeeting::createFirstPhilosopher()
{
    philosophers_.emplace_back(*logger_,
                               forks_[0].get(),   // first fork as left fork
                               forks_[tableSize_ - 1].get(),   // last fork as right fork
                               *this,
                               0);
}

void PhilosophyMeeting::createMiddlePhilosophers()
{
    for (auto i = 1; i < tableSize_ - 1; ++i) {
        philosophers_.emplace_back(*logger_,
                                   forks_[i].get(),
                                   forks_[i - 1].get(),
                                   *this,
                                   i);
    }
}

void PhilosophyMeeting::createLastPhilosopher()
{
    philosophers_.emplace_back(*logger_,
                               forks_[tableSize_ - 1].get(),   // last fork as left fork
                               forks_[tableSize_ - 2].get(),   // second-last fork as right fork
                               *this,
                               tableSize_ - 1);
}

void PhilosophyMeeting::describeTableArrangement() const
{
    std::ostringstream descriptionSS;
    descriptionSS << "Table arrangement:\n";
    descriptionSS << "=======================================\n";

    for (const auto& philosopher : philosophers_) {
        descriptionSS << "Philosopher " << philosopher.id() << " forks:\n"
                      << "\t\tleft fork id: " << philosopher.leftForkId() << '\n'
                      << "\t\tright for id: " << philosopher.rightForkId() << '\n'
                      << "------------------------------------------\n";
    }
    descriptionSS << "=======================================\n";

    *logger_ << descriptionSS.str();
}
