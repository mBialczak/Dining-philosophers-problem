#include "PhilosophyMeeting.hpp"

#include "Logger.hpp"

#include <algorithm>
#include <sstream>

PhilosophyMeeting::PhilosophyMeeting(std::ostream& streamToLog,
                                     int tableSize,
                                     int mealsToServe,
                                     std::chrono::milliseconds mealDuration,
                                     bool shouldShareMealsEqually)
    : logger_(std::make_unique<Logger>(streamToLog)),
      tableSize_(tableSize),
      meals_(mealsToServe)
{
    createForks();
    createPhilosophers(mealDuration, shouldShareMealsEqually);
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

void PhilosophyMeeting::createPhilosophers(std::chrono::milliseconds mealDuration,
                                           bool shouldShareEqually)
{
    philosophers_.reserve(tableSize_);

    createFirstPhilosopher(mealDuration, shouldShareEqually);
    createMiddlePhilosophers(mealDuration, shouldShareEqually);
    createLastPhilosopher(mealDuration, shouldShareEqually);
}

void PhilosophyMeeting::createFirstPhilosopher(std::chrono::milliseconds mealDuration,
                                               bool shouldShareEqually)
{
    // philosophers_.emplace_back(*logger_,
    //                            forks_[0].get(),   // first fork as left fork
    //                            forks_[tableSize_ - 1].get(),   // last fork as right fork
    //                            *this,
    //                            0);
    // TODO: VERIFY
    philosophers_.emplace_back(std::make_unique<Philosopher>(*logger_,
                                                             forks_[0].get(),   // first fork as left fork
                                                             forks_[tableSize_ - 1].get(),   // last fork as right fork
                                                             *this,
                                                             0,
                                                             mealDuration,
                                                             shouldShareEqually));
}

void PhilosophyMeeting::createMiddlePhilosophers(std::chrono::milliseconds mealDuration,
                                                 bool shouldShareEqually)
{
    // for (auto i = 1; i < tableSize_ - 1; ++i) {
    //     philosophers_.emplace_back(*logger_,
    //                                forks_[i].get(),
    //                                forks_[i - 1].get(),
    //                                *this,
    //                                i);
    // }
    for (auto i = 1; i < tableSize_ - 1; ++i) {
        philosophers_.emplace_back(std::make_unique<Philosopher>(*logger_,
                                                                 forks_[i].get(),
                                                                 forks_[i - 1].get(),
                                                                 *this,
                                                                 i,
                                                                 mealDuration,
                                                                 shouldShareEqually));
    }
}

void PhilosophyMeeting::createLastPhilosopher(std::chrono::milliseconds mealDuration,
                                              bool shouldShareEqually)
{
    // philosophers_.emplace_back(*logger_,
    //                            forks_[tableSize_ - 1].get(),   // last fork as left fork
    //                            forks_[tableSize_ - 2].get(),   // second-last fork as right fork
    //                            *this,
    //                            tableSize_ - 1);
    philosophers_.emplace_back(std::make_unique<Philosopher>(*logger_,
                                                             forks_[tableSize_ - 1].get(),   // last fork as left fork
                                                             forks_[tableSize_ - 2].get(),   // second-last fork as right fork
                                                             *this,
                                                             tableSize_ - 1,
                                                             mealDuration,
                                                             shouldShareEqually));
}

// TODO:
void PhilosophyMeeting::startEatingDiscussion()
{
    for (auto i = 0; i < tableSize_; ++i) {
        // threads_.emplace_back(&Philosopher::tryToEat, &philosophers_[i]);
        // TODO: VERIFY
        threads_.emplace_back(&Philosopher::tryToEat, philosophers_[i].get());
    }
}
// TODO: VERIFY
void PhilosophyMeeting::summarizeMeeting()
{
    for (auto&& thread : threads_) {
        thread.join();
    }
    std::ostringstream message;
    message << "==================================\n"
            << "Meeting ended\n"
            << "Meals left: " << meals_ << "\n"
            << "----------------------------------\n";
    for (auto&& philosopher : philosophers_) {
        message << "Philosopher " << philosopher->id()
                << " has eaten " << philosopher->mealsEaten() << " meals"
                << "\n"
                << "-------------------------------\n";
    }
    *logger_ << message.str();
}

void PhilosophyMeeting::describeTableArrangement() const
{
    std::ostringstream descriptionSS;
    descriptionSS << "Table arrangement:\n";
    descriptionSS << "=======================================\n";

    for (const auto& philosopher : philosophers_) {
        descriptionSS << "Philosopher " << philosopher->id() << " forks:\n"
                      << "\t\tleft fork id: " << philosopher->leftForkId() << '\n'
                      << "\t\tright for id: " << philosopher->rightForkId() << '\n'
                      << "------------------------------------------\n";
    }
    descriptionSS << "=======================================\n";

    *logger_ << descriptionSS.str();
}

int PhilosophyMeeting::leastNumberOfEatenMeals()   // TODO: VERIFY
{
    auto iterToMostHungry = std::min_element(philosophers_.begin(),
                                             philosophers_.end(),
                                             [this](const auto& phOne, const auto& phTwo) {
                                                 return phOne->mealsEaten() < phTwo->mealsEaten();
                                             });
    return (*iterToMostHungry)->mealsEaten();
}

bool PhilosophyMeeting::serveMeal()
{
    std::lock_guard mealsLock(mealsMtx_);
    if (meals_) {
        --meals_;
        return true;
    }
    return false;
}

int PhilosophyMeeting::mealsLeft()
{
    std::shared_lock mealsLock(mealsMtx_);
    return meals_;
}