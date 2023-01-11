#pragma once

#include <iostream>
#include <mutex>

class Logger
{
  public:
    explicit Logger(std::ostream& stream = std::cout);
    template <typename typeToPrint>
    void print(const typeToPrint& txt) const;   // TODO: VERIFY if needed

  private:
    std::ostream& stream_;
    mutable std::mutex coutMtx_;
};

Logger& operator<<(Logger& logger, const std::string& txt);

// TODO: VERIFY
// template <typename typeToPrint>
// Logger& operator<<(Logger& logger, typeToPrint& toPrint)
// {
//     std::lock_guard streamLock(coutMtx_);
//     stream_ << toPrint << std::endl;

//     return logger;
// }