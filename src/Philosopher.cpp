#include "Philosopher.hpp"

#include "Fork.hpp"
#include "PhilosophyMeeting.hpp"

#include <sstream>

Philosopher::Philosopher(Logger& logger,
                         Fork* leftFork,
                         Fork* rightFork,
                         PhilosophyMeeting& meeting,
                         int id,
                         std::chrono::milliseconds mealDuration,
                         bool shouldShareMealsEqually)
    : logger_(logger),
      leftFork_(leftFork),
      rightFork_(rightFork),
      meeting_(meeting),
      id_(id),
      mealsEaten_(0),
      mealDuration_(mealDuration),
      shareEqually_(shouldShareMealsEqually)
{ }

// TODO:
void Philosopher::tryToEat()
{
    // TODO: VERIFY
    while (meeting_.mealsLeft() > 0) {
        // TODO: VERIFY
        // if (mealsEaten() <= meeting_.leastNumberOfEatenMeals()) {
        // std::ostringstream message;
        // message << "Aquired forks: " << leftFork_->id() << " and " << rightFork_->id() << "\n";
        // logger_ << message.str();
        // meeting_.serveMeal();
        if (!shareEqually_
            || mealsEaten() <= meeting_.leastNumberOfEatenMeals()) {
            // eat();
            bool wasMealServed = requestMeal();
            increaseOwnMealsCount(wasMealServed);
            std::this_thread::sleep_for(mealDuration_);
        }
        // }
        // std::scoped_lock bothForksLock(leftFork_->getMtx(), rightFork_->getMtx());
        // std::ostringstream message;
        // message << "Aquired forks: " << leftFork_->id() << " and " << rightFork_->id() << "\n";
        // logger_ << message.str();
        // meeting_.serveMeal();
        // eat();
    }
}

// void Philosopher::eat()
// {
//     // std::scoped_lock bothForksLock(leftFork_->getMtx(), rightFork_->getMtx());// TODO: REMOVE

//     // bool wasMealGiven = meeting_.serveMeal();// TODO: REMOVE
//     // std::lock_guard mealsEatenLock(mealsEatenMtx_);
//     // if (wasMealGiven) {
//     //     ++mealsEaten_;
//     // }
// }

bool Philosopher::requestMeal()
{
    // We request meal only if both forks available
    std::scoped_lock bothForksLock(leftFork_->getMtx(), rightFork_->getMtx());
    // TODO: REMOVE

    // test_.lock();
    return meeting_.serveMeal();
}

void Philosopher::increaseOwnMealsCount(bool wasMealServed)
{
    if (wasMealServed) {
        std::lock_guard lock(mealsEatenMtx_);
        ++mealsEaten_;
    }
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

int Philosopher::mealsEaten() const
{
    std::shared_lock mealsEatenLock(mealsEatenMtx_);

    return mealsEaten_;
}