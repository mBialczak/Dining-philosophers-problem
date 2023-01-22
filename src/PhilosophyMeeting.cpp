#include "PhilosophyMeeting.hpp"

#include "Logger.hpp"

#include <algorithm>
#include <sstream>

PhilosophyMeeting::PhilosophyMeeting(std::ostream& streamToLog,
                                     unsigned tableSize,
                                     int mealsToServe,
                                     std::chrono::microseconds mealDuration,
                                     bool shouldShareMealsEqually,
                                     bool fullLogging)
    : logger_(streamToLog),
      tableSize_(tableSize),
      meals_(mealsToServe)
{
    createForks();
    createPhilosophers(mealDuration, shouldShareMealsEqually, fullLogging);

    logSettings(mealDuration,
                shouldShareMealsEqually,
                fullLogging);

    if (fullLogging) {

        describeTableArrangement();
    }
}

void PhilosophyMeeting::createForks()
{
    forks_.reserve(tableSize_);
    for (unsigned i = 0; i < tableSize_; i++) {
        forks_.emplace_back(std::make_unique<Fork>(i));
    }
}

void PhilosophyMeeting::createPhilosophers(std::chrono::microseconds mealDuration,
                                           bool shouldShareEqually,
                                           bool fullLogging)
{
    philosophers_.reserve(tableSize_);
    createFirstPhilosopher(mealDuration, shouldShareEqually, fullLogging);
    createMiddlePhilosophers(mealDuration, shouldShareEqually, fullLogging);
    createLastPhilosopher(mealDuration, shouldShareEqually, fullLogging);
}

void PhilosophyMeeting::createFirstPhilosopher(std::chrono::microseconds mealDuration,
                                               bool shouldShareEqually,
                                               bool fullLogging)
{
    philosophers_.emplace_back(std::make_unique<Philosopher>(logger_,
                                                             forks_[0].get(),
                                                             forks_[tableSize_ - 1].get(),
                                                             *this,
                                                             0,
                                                             mealDuration,
                                                             shouldShareEqually,
                                                             fullLogging));
}

void PhilosophyMeeting::createMiddlePhilosophers(std::chrono::microseconds mealDuration,
                                                 bool shouldShareEqually,
                                                 bool fullLogging)
{
    for (unsigned i = 1; i < tableSize_ - 1; ++i) {
        philosophers_.emplace_back(std::make_unique<Philosopher>(logger_,
                                                                 forks_[i].get(),
                                                                 forks_[i - 1].get(),
                                                                 *this,
                                                                 i,
                                                                 mealDuration,
                                                                 shouldShareEqually,
                                                                 fullLogging));
    }
}

void PhilosophyMeeting::createLastPhilosopher(std::chrono::microseconds mealDuration,
                                              bool shouldShareEqually,
                                              bool fullLogging)
{
    philosophers_.emplace_back(std::make_unique<Philosopher>(logger_,
                                                             forks_[tableSize_ - 1].get(),
                                                             forks_[tableSize_ - 2].get(),
                                                             *this,
                                                             tableSize_ - 1,
                                                             mealDuration,
                                                             shouldShareEqually,
                                                             fullLogging));
}

void PhilosophyMeeting::startEatingDiscussion()
{
    threads_.reserve(tableSize_);
    logMeetingStart();
    meetingStartTime_ = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < tableSize_; ++i) {
        threads_.emplace_back(&Philosopher::tryToEat, philosophers_[i].get());
    }
}

void PhilosophyMeeting::summarizeMeeting()
{
    for (auto&& thread : threads_) {
        thread.join();
    }
    meetingEndTime_ = std::chrono::high_resolution_clock::now();
    logSummaryMessage();
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

    logger_ << descriptionSS.str();
}

int PhilosophyMeeting::findMostHungryPhilosopher() const
{
    auto iterToMostHungry = std::min_element(philosophers_.begin(),
                                             philosophers_.end(),
                                             [](const auto& phOne, const auto& phTwo) {
                                                 return phOne->mealsEaten() < phTwo->mealsEaten();
                                             });
    return (*iterToMostHungry)->mealsEaten();
}

void PhilosophyMeeting::logSettings(std::chrono::microseconds mealDuration,
                                    bool shouldShareMealsEqually,
                                    bool fullLogging) const
{
    std::ostringstream message;
    message << "========= Settings =========\n"
            << "number of philosophers / forks: " << tableSize_ << '\n'
            << "meals to serve: " << meals_ << '\n'
            << "meal duration [microseconds] " << mealDuration.count() << '\n'
            << "equal meal share: " << (shouldShareMealsEqually ? "true" : "false") << '\n'
            << "logging: " << (fullLogging ? "full" : "abbreviated") << '\n';

    logger_ << message.str();
}

void PhilosophyMeeting::logMeetingStart()
{
    std::ostringstream message;
    message << "The duration of the meeting (only the multithreaded part) will be measured.\n\n"
            << "========= Meeting (the multithreaded part) starts =========";
    logger_ << message.str();
}

void PhilosophyMeeting::logSummaryMessage() const
{
    std::chrono::duration<double> meetingDuration = meetingEndTime_ - meetingStartTime_;
    std::ostringstream message;
    message << "\n========= Meeting (the multithreaded part) ended =============\n"
            << "Meals left: " << meals_ << "\n"
            << "Meeting (multithreaded part) duration: " << meetingDuration.count() << " seconds\n"
            << "----------------------------------\n";
    for (auto&& philosopher : philosophers_) {
        message << "Philosopher " << philosopher->id()
                << " has eaten " << philosopher->mealsEaten() << " meals"
                << "\n"
                << "-------------------------------\n";
    }
    logger_ << message.str();
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

int PhilosophyMeeting::mealsLeft() const
{
    std::shared_lock mealsLock(mealsMtx_);
    return meals_;
}