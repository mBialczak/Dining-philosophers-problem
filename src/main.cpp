#include "PhilosophyMeeting.hpp"

#include <iostream>
#include <sstream>

using ParseResult = std::tuple<unsigned, int, int, bool, bool>;

ParseResult parseArgs(int argsNumber, char** argumentsArray);
ParseResult parseAllProvided(char** argumentsArray);
ParseResult provideDefaults();
void printInstructionIfUnexpectedNumberOfArgs(int providedArgsNumber);

constexpr int expectedNumberOfArgs { 5 };
constexpr unsigned defaultPhilosophersNumber { 5 };
constexpr int defaultMealsNumber { 3000 };
constexpr int defaultMealDuration { 0 };
constexpr bool defaultSharingSetting { true };
constexpr bool defaultFullLoggingSetting { false };

int main(int args, char** argv)
{
    using namespace std::literals::chrono_literals;

    auto [philosophersNumber, meals, mealDuration, equalShare, fullLogging] = parseArgs(args, argv);

    if (philosophersNumber < 2) {
        std::cout << "Philosophers/forks number must be grater or equal to 2!\n"
                  << "I am quitting. Try again!\n";
        return -1;
    }

    PhilosophyMeeting meeting { std::cout,
                                philosophersNumber,
                                meals,
                                std::chrono::microseconds(mealDuration),
                                static_cast<bool>(equalShare),
                                static_cast<bool>(fullLogging) };

    meeting.startEatingDiscussion();
    meeting.summarizeMeeting();
}

ParseResult parseArgs(int argsNumber, char** argumentsArray)
{
    printInstructionIfUnexpectedNumberOfArgs(argsNumber);

    return argsNumber == expectedNumberOfArgs + 1 ? parseAllProvided(argumentsArray)
                                                  : provideDefaults();
}

ParseResult parseAllProvided(char** argumentsArray)
{
    return std::tuple { std::stoi(argumentsArray[1]),   // number of philosophers == number of forks
                        std::stoi(argumentsArray[2]),   // total number of meals to serve
                        std::stoi(argumentsArray[3]),   // duration of meal eaten by each philosopher
                        std::stoi(argumentsArray[4]),   // should meals be divided as equally as possible
                        std::stoi(argumentsArray[5]) };   // should print provide full log
}

ParseResult provideDefaults()
{
    return std::tuple { defaultPhilosophersNumber,
                        defaultMealsNumber,
                        defaultMealDuration,
                        defaultSharingSetting,
                        defaultFullLoggingSetting };
}

void printInstructionIfUnexpectedNumberOfArgs(int providedArgsNumber)
{
    if (providedArgsNumber - 1 != expectedNumberOfArgs) {
        std::ostringstream message;
        message << "The number of provided arguments is different then " << expectedNumberOfArgs << " expected!\n\n"
                << "Defaults will be used until you decide to use them all - sorry :)\n\n"
                << "All " << expectedNumberOfArgs << " arguments are expected to provide full functionality.\n"
                << "----------------------------------------------------\n"
                << "NOTE: all arguments are numeric values!\n"
                << "- 1st argument -> the number of philosophers (and forks as well).\n"
                << "\tDEFAULT VALUE -> " << defaultPhilosophersNumber << '\n'
                << "\tPlease note, that it will be equal to number of threads used.\n"
                << "\tOne additional thread (will always run - the main thread).\n"
                << "\tNOTE: Threads number suported by your system is: "
                << std::thread::hardware_concurrency() << "\n"
                << "\tYou can set the number of philosophers to higher amount than this\n"
                << "\tand observe the influence on excecution time for example.\n\n"

                << "- 2nd argument -> total number of meals to serve.\n"
                << "\tDEFAULT VALUE -> " << defaultMealsNumber << "\n\n"

                << "- 3rd argument ->  duration of meal in microseconds\n"
                << "\tDEFAULT VALUE -> " << defaultMealDuration << "\n\n"

                << "- 4th argument -> 0/1 boolean for setting equal sharing of meals\n"
                << "\t 0 - no sharing (the system thread scheduler determines final result)\n"
                << "\t 1 - equal sharing (less efficient but no philosopher will leave hungry ;)\n"
                << "\tDEFAULT VALUE -> " << defaultSharingSetting << "\n\n"

                << "- 5th argument -> 0/1 boolean determining if full log should be provided\n"
                << "\t 0 - abbreviated log\n"
                << "\t 1 - full log (NOT RECOMMENDED FOR HIGH MEALS NUMBER VALUES)\n"
                << "\tDEFAULT VALUE -> " << defaultFullLoggingSetting << "\n\n";
        std::cout << message.str();
    }
}