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
                PhilosophyMeeting& meeting);

  private:
    Logger& logger_;
    Fork* leftFork_;
    Fork* rightFork_;
    PhilosophyMeeting& meeting_;
};