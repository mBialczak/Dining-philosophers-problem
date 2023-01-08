#pragma once

class Logger;
class Fork;
class PhilosophyMeeting;

class Philosopher
{
    Philosopher(Logger* const logger,
                Fork& leftFork,
                Fork& rightFork,
                PhilosophyMeeting& meeting);

  private:
    Logger* const logger_;
    Fork& leftFork_;
    Fork& rightFork_;
    PhilosophyMeeting& meeting_;
};