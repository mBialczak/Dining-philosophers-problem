#pragma once

#include "Fork.hpp"
#include "Philosopher.hpp"

#include <array>
#include <atomic>
#include <chrono>
#include <memory>
#include <shared_mutex>
#include <thread>
#include <vector>

class Logger;

class PhilosophyMeeting
{
  public:
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

    PhilosophyMeeting(std::ostream& streamToLog,
                      unsigned tableSize,
                      int mealsToServe,
                      std::chrono::microseconds mealDuration,
                      bool shouldShareMealsEqually,
                      bool fullLogging);
    void startEatingDiscussion();
    void summarizeMeeting();
    bool serveMeal();
    int mealsLeft() const;
    int findMostHungryPhilosopher() const;

  private:
    void createForks();
    void createFirstPhilosopher(std::chrono::microseconds mealDuration);
    void createMiddlePhilosophers(std::chrono::microseconds mealDuration);
    void createLastPhilosopher(std::chrono::microseconds mealDuration);
    void logMeetingStart();
    void logSettings(std::chrono::microseconds mealDuration,
                     bool shouldShareMealsEqually,
                     bool fullLogging) const;
    void logSummaryMessage() const;
    void describeTableArrangement() const;

    Logger logger_;
    const unsigned tableSize_;
    std::vector<std::unique_ptr<Fork>> forks_;
    std::vector<std::unique_ptr<Philosopher>> philosophers_;
    std::vector<std::thread> threads_;
    std::atomic<int> meals_;
    const bool shareEqually_;
    const bool fullLogging_;
    TimePoint meetingStartTime_;
    TimePoint meetingEndTime_;
};