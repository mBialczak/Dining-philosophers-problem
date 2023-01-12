#pragma once

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
                std::chrono::milliseconds mealDuration,
                bool shouldShareMealsEqually,
                bool fullLogging);
    void tryToEat();   // TODO: VERIFY const
    int id() const;
    int leftForkId() const;
    int rightForkId() const;
    int mealsEaten() const;

  private:
    bool requestMeal() const;
    void increaseOwnMealsCount(bool wasMealServed);
    void logEatingMessage() const;
    void logOthersMoreHungryMessage() const;

    Logger& logger_;
    Fork* leftFork_;
    Fork* rightFork_;
    PhilosophyMeeting& meeting_;
    const int id_;
    const std::chrono::milliseconds mealDuration_;
    const bool shareEqually_;
    const bool fullLogging_;
    mutable std::shared_mutex mealsEatenMtx_;
    int mealsEaten_;
    mutable std::map<std::thread::id, int> shortThreadIds_;
};