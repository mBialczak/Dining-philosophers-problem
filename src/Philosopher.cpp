#include "Philosopher.hpp"

#include "Fork.hpp"
#include "PhilosophyMeeting.hpp"

#include <sstream>

Philosopher::Philosopher(Logger& logger,
                         Fork* leftFork,
                         Fork* rightFork,
                         PhilosophyMeeting& meeting,
                         int id,
                         std::chrono::microseconds mealDuration,
                         bool shouldShareMealsEqually,
                         bool fullLogging)
    : logger_(logger),
      leftFork_(leftFork),
      rightFork_(rightFork),
      meeting_(meeting),
      id_(id),
      mealDuration_(mealDuration),
      shareEqually_(shouldShareMealsEqually),
      fullLogging_(fullLogging),
      mealsEaten_(0)
{ }

void Philosopher::tryToEat()
{
    while (meeting_.mealsLeft() > 0) {
        if (shareEqually_) {
            if (isAmongMostHungry()) {
                eat();
            }
            else {
                if (fullLogging_) {
                    logOthersMoreHungryMessage();
                }
            }
        }
        else {
            eat();
        }
    }
}

void Philosopher::eat()
{
    bool wasMealServed = requestMeal();
    increaseOwnMealsCount(wasMealServed);
    std::this_thread::sleep_for(mealDuration_);
}

bool Philosopher::isAmongMostHungry() const
{
    return mealsEaten() <= meeting_.findMostHungryPhilosopher();
}

bool Philosopher::requestMeal() const
{
    std::scoped_lock bothForksLock(leftFork_->getMtx(), rightFork_->getMtx());
    if (fullLogging_) {
        logEatingMessage();
    }

    return meeting_.serveMeal();
}

void Philosopher::increaseOwnMealsCount(bool wasMealServed)
{
    if (wasMealServed) {
        std::lock_guard lock(mealsEatenMtx_);
        ++mealsEaten_;
    }
}

int Philosopher::mealsEaten() const
{
    std::shared_lock mealsEatenLock(mealsEatenMtx_);

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