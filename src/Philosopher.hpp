#pragma once

#include <atomic>
#include <map>
#include <shared_mutex>
#include <thread>

class Logger;
class Fork;
class PhilosophyMeeting;

class Philosopher
{
  public:
    Philosopher(Logger& logger,
                Fork* leftFork,
                Fork* rightFork,
                PhilosophyMeeting& meeting,
                int id,
                std::chrono::microseconds mealDuration);
    void tryToEat(bool shareEqually, bool fullLogging);
    int id() const;
    int leftForkId() const;
    int rightForkId() const;
    int mealsEaten() const;

  private:
    void eat(bool fullLogging);
    bool requestMeal(bool fullLogging) const;
    void increaseOwnMealsCount(bool wasMealServed);
    void logEatingMessage() const;
    void logOthersMoreHungryMessage() const;
    bool isAmongMostHungry() const;

    Logger& logger_;
    Fork* leftFork_;
    Fork* rightFork_;
    PhilosophyMeeting& meeting_;
    const int id_;
    const std::chrono::microseconds mealDuration_;
    std::atomic<int> mealsEaten_;
};