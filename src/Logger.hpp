#pragma once

#include <iostream>
#include <mutex>

class Logger
{
  public:
    explicit Logger(std::ostream& stream = std::cout);
    void print(const std::string& txt) const;   // TODO: VERIFY if needed

  private:
    std::ostream& stream_;
    mutable std::mutex coutMtx_;
};

Logger& operator<<(Logger& logger, const std::string& txt);