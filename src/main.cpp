#include "PhilosophyMeeting.hpp"

#include <iostream>

std::tuple<int, int, int, bool, bool> parseArgs(int argsNumber, char** argumentsArray);
std::tuple<int, int, int, bool, bool> parseAllProvided(char** argumentsArray);
std::tuple<int, int, int, bool, bool> provideDefaults();

int main(int arg, char** argv)
{
    using namespace std::literals::chrono_literals;

    auto [philosophersNumber, meals, mealDuration, equalShare, fullLogging] = parseArgs(arg, argv);

    PhilosophyMeeting meeting { std::cout,
                                philosophersNumber,
                                meals,
                                std::chrono::milliseconds(mealDuration),
                                static_cast<bool>(equalShare),
                                static_cast<bool>(fullLogging) };

    meeting.startEatingDiscussion();
    meeting.summarizeMeeting();
}

std::tuple<int, int, int, bool, bool> parseArgs(int argsNumber, char** argumentsArray)
{
    return argsNumber == 6 ? parseAllProvided(argumentsArray)
                           : provideDefaults();
}

std::tuple<int, int, int, bool, bool> parseAllProvided(char** argumentsArray)
{
    return std::tuple { std::stoi(argumentsArray[1]),   // number of philosophers == number of forks
                        std::stoi(argumentsArray[2]),   // total number of meals to serve
                        std::stoi(argumentsArray[3]),   // duration of meal eaten by each philosopher in ms
                        std::stoi(argumentsArray[4]),
                        std::stoi(argumentsArray[5]) };   // should meals be divided as equally as possible
}

std::tuple<int, int, int, bool, bool> provideDefaults()
{
    return std::tuple { 5,   // number of philosophers == number of forks
                        3000,   // total number of meals to serve
                        10,   // duration of meal eaten by each philosopher in miliseconds
                        true,
                        false };   // should meals be divided as equally as possible
}