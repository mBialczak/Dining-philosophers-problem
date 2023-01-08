#pragma once

#include <memory>
#include <shared_mutex>
#include <thread>
#include <vector>

class Fork;
class Logger;
class Philosopher;

class PhilosophyMeeting
{
    PhilosophyMeeting(std::ostream& streamToLog, int tableSize, int mealsToServe);

  private:
    void createForks();

    std::unique_ptr<Logger> logger_;   // TODO: VERIFY if we want unique or shared
    const int tableSize_;
    int meals_;
    std::vector<std::unique_ptr<Fork>> forks_;   // TODO: VERIFY
    // std::vector<Philosopher> philosophers_;
    std::vector<std::thread> threads_;
    std::shared_mutex mealsMtx_;
};