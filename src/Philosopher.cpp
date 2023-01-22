#include "Philosopher.hpp"

#include "Fork.hpp"
#include "PhilosophyMeeting.hpp"

#include <sstream>

Philosopher::Philosopher(Logger& logger,
                         Fork* leftFork,
                         Fork* rightFork,
                         PhilosophyMeeting& meeting,
                         int id,
                         std::chrono::microseconds mealDuration)
    : logger_(logger),
      leftFork_(leftFork),
      rightFork_(rightFork),
      meeting_(meeting),
      id_(id),
      mealDuration_(mealDuration),
      mealsEaten_(0)
{ }

void Philosopher::tryToEat(bool shareEqually, bool fullLogging)
{
    while (meeting_.mealsLeft() > 0) {
        if (shareEqually) {
            if (isAmongMostHungry()) {
                eat(fullLogging);
            }
            else {
                if (fullLogging) {
                    logOthersMoreHungryMessage();
                }
            }
        }
        else {
            eat(fullLogging);
        }
    }
}

void Philosopher::eat(bool fullLogging)
{
    bool wasMealServed = requestMeal(fullLogging);
    increaseOwnMealsCount(wasMealServed);
    std::this_thread::sleep_for(mealDuration_);
}

bool Philosopher::isAmongMostHungry() const
{
    return mealsEaten() <= meeting_.findMostHungryPhilosopher();
}

bool Philosopher::requestMeal(bool fullLogging) const
{
    std::scoped_lock bothForksLock(leftFork_->getMtx(), rightFork_->getMtx());
    if (fullLogging) {
        logEatingMessage();
    }

    return meeting_.serveMeal();
}

void Philosopher::increaseOwnMealsCount(bool wasMealServed)
{
    if (wasMealServed) {
        ++mealsEaten_;
    }
}

int Philosopher::mealsEaten() const
{
    return mealsEaten_;
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

void Philosopher::logEatingMessage() const
{
    std::ostringstream ss;
    ss << "thread [" << std::this_thread::get_id() << "]-> "
       << "Philosopher " << std::to_string(id_)
       << " aquired forks "
       << leftFork_->id() << " and " << rightFork_->id()
       << " and IS EATING";
    logger_ << ss.str();
}

void Philosopher::logOthersMoreHungryMessage() const
{
    std::ostringstream ss;
    ss << "thread [" << std::this_thread::get_id() << "]-> "
       << "Philosopher " << std::to_string(id_)
       << " decides others are more hungry and is THINKING until his turn";
    logger_ << ss.str();
}