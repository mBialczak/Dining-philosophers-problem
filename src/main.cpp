#include "PhilosophyMeeting.hpp"

#include <iostream>

std::tuple<int, int, int, bool> parseArgs(int argsNumber, char** argumentsArray);
std::tuple<int, int, int, bool> parseAllProvided(int argsNumber, char** argumentsArray);
std::tuple<int, int, int, bool> provideDefaults();

int main([[maybe_unused]] int arg, [[maybe_unused]] char** argv)
{
    using namespace std::literals::chrono_literals;

    PhilosophyMeeting meeting { std::cout,
                                5,
                                600,
                                0ms,
                                false };
    meeting.startEatingDiscussion();
    meeting.summarizeMeeting();
}

std::tuple<int, int, int, bool> parseArgs(int argsNumber, char** argumentsArray)
{
    return argsNumber == 5 ? parseAllProvided(argsNumber, argumentsArray)
                           : provideDefaults();
}

std::tuple<int, int, int, bool> parseArgs(int argsNumber, char** argumentsArray)
{
    return { argumentsArray[1],   // number of philosophers == number of forks
             argumentsArray[2],   // total number of meals to serve
             argumentsArray[3],   // duration of meal eaten by each philosopher in miliseconds
             argumentsArray[4] };   // should meals be divided as equally as possible
}