#include "Philosopher.hpp"

#include "Fork.hpp"
#include "PhilosophyMeeting.hpp"

Philosopher::Philosopher(Logger& logger,
                         Fork* leftFork,
                         Fork* rightFork,
                         PhilosophyMeeting& meeting,
                         int id)
    : logger_(logger),
      leftFork_(leftFork),
      rightFork_(rightFork),
      meeting_(meeting),
      id_(id)

{ }

// TODO:
void Philosopher::tryToEat()
{
}

int Philosopher::id() const
{
    return id_;
}

int Philosopher::leftForkId() const
{
    return leftFork_ ? leftFork_->id()
                     : -1;
}

int Philosopher::rightForkId() const
{
    return rightFork_ ? rightFork_->id()
                      : -1;
}