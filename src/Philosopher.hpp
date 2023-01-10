#pragma once

class Logger;
class Fork;
class PhilosophyMeeting;

class Philosopher
{
  public:
    Philosopher(Logger& logger,
                Fork* leftFork,
                Fork* rightFork,
                PhilosophyMeeting& meeting,
                int id);
    void tryToEat();
    int id() const;
    int leftForkId() const;
    int rightForkId() const;

  private:
    Logger& logger_;
    Fork* leftFork_;
    Fork* rightFork_;
    PhilosophyMeeting& meeting_;
    const int id_;
};