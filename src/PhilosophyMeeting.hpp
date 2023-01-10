#pragma once

#include "Fork.hpp"
#include "Philosopher.hpp"

#include <memory>
#include <shared_mutex>
#include <thread>
#include <vector>

class Logger;

class PhilosophyMeeting
{
  public:
    PhilosophyMeeting(std::ostream& streamToLog, int tableSize, int mealsToServe);
    // void startEatingDiscussion(); // TODO:

  private:
    void createForks();
    void createPhilosophers();
    void createFirstPhilosopher();
    void createMiddlePhilosophers();
    void createLastPhilosopher();
    void describeTableArrangement() const;
    // void serveMeal(); // TODO: or something else to decrese number of meals
    // int mealsLeft(); // TODO:

    std::unique_ptr<Logger> logger_;   // TODO: VERIFY if we want unique or shared
    const int tableSize_;
    int meals_;
    std::vector<std::unique_ptr<Fork>> forks_;   // TODO: try make without unique
    std::vector<Philosopher> philosophers_;   // // TODO: consider unique_ptr
    std::vector<std::thread> threads_;
    std::shared_mutex mealsMtx_;
};