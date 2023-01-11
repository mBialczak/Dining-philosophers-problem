#pragma once

#include <shared_mutex>

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
                bool shouldShareMealsEqually);
    void tryToEat();   // TODO: VERIFY const
    int id() const;
    int leftForkId() const;
    int rightForkId() const;
    int mealsEaten() const;

  private:
    void eat();   // TODO: REMOVE
    bool requestMeal();   // TODO: VERIFY const?
    void increaseOwnMealsCount(bool wasMealServed);

    Logger& logger_;
    Fork* leftFork_;
    Fork* rightFork_;
    PhilosophyMeeting& meeting_;
    const int id_;
    int mealsEaten_;
    const std::chrono::milliseconds mealDuration_;
    const bool shareEqually_;
    mutable std::shared_mutex mealsEatenMtx_;
    // TODO: REMOVE
    std::mutex test_;
};