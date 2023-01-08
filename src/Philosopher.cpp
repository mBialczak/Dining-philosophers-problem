#include "Philosopher.hpp"

#include "PhilosophyMeeting.hpp"

Philosopher::Philosopher(Logger* const logger,
                         Fork& rightFork,
                         Fork& leftFork,
                         PhilosophyMeeting& meeting)
    : logger_(logger),
      leftFork_(leftFork),
      rightFork_(rightFork),
      meeting_(meeting)

{ }