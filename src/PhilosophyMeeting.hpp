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
    PhilosophyMeeting(std::ostream& streamToLog,
                      int tableSize,
                      int mealsToServe,
                      std::chrono::milliseconds mealDuration,
                      bool shouldShareMealsEqually = true);
    void startEatingDiscussion();   // TODO:
    void summarizeMeeting();
    bool serveMeal();   // TODO: or something else to decrese number of meals
    int mealsLeft();   // TODO: verify
    int leastNumberOfEatenMeals();   // TODO: VERIFY const especially

  private:
    void createForks();
    void createPhilosophers(std::chrono::milliseconds mealDuration,
                            bool shouldShareEqually);
    void createFirstPhilosopher(std::chrono::milliseconds mealDuration,
                                bool shouldShareEqually);
    void createMiddlePhilosophers(std::chrono::milliseconds mealDuration,
                                  bool shouldShareEqually);
    void createLastPhilosopher(std::chrono::milliseconds mealDuration,
                               bool shouldShareEqually);
    void describeTableArrangement() const;

    std::unique_ptr<Logger> logger_;   // TODO: VERIFY if we want unique or shared
    const int tableSize_;
    int meals_;
    std::vector<std::unique_ptr<Fork>> forks_;   // TODO: try make without unique
    // std::vector<Philosopher> philosophers_;   // // TODO: consider unique_ptr
    std::vector<std::unique_ptr<Philosopher>> philosophers_;   // // TODO: consider unique_ptr
    // TODO: VERIFY
    // std::array<Philosopher, 8> philosophers2_;   // TODO: VERIFY
    std::vector<std::thread> threads_;
    mutable std::shared_mutex mealsMtx_;   // TODO: VERIFY if shared
};