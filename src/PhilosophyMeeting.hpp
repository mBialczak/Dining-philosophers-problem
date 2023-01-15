#pragma once

#include "Fork.hpp"
#include "Philosopher.hpp"

#include <array>
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
                      int tableSize,
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
    void createPhilosophers(std::chrono::microseconds mealDuration,
                            bool shouldShareEqually,
                            bool fullLogging);
    void createFirstPhilosopher(std::chrono::microseconds mealDuration,
                                bool shouldShareEqually,
                                bool fullLogging);
    void createMiddlePhilosophers(std::chrono::microseconds mealDuration,
                                  bool shouldShareEqually,
                                  bool fullLogging);
    void createLastPhilosopher(std::chrono::microseconds mealDuration,
                               bool shouldShareEqually,
                               bool fullLogging);
    void logMeetingStart();
    void logSettings(int tableSize,
                     int mealsToServe,
                     std::chrono::microseconds mealDuration,
                     bool shouldShareMealsEqually,
                     bool fullLogging) const;
    void logSummaryMessage() const;
    void describeTableArrangement() const;

    Logger logger_;
    const int tableSize_;
    std::vector<std::unique_ptr<Fork>> forks_;
    std::vector<std::unique_ptr<Philosopher>> philosophers_;
    std::vector<std::thread> threads_;
    int meals_;
    mutable std::shared_mutex mealsMtx_;
    TimePoint meetingStartTime_;
    TimePoint meetingEndTime_;
};