#pragma once

#include <iostream>
#include <mutex>

class Logger
{
  public:
    explicit Logger(std::ostream& stream);
    void print(const std::string& txt) const;

  private:
    std::ostream& stream_;
    mutable std::mutex coutMtx_;
};

const Logger& operator<<(const Logger& logger, const std::string& txt);
