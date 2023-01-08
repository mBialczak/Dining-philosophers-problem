#include "Logger.hpp"

Logger::Logger(std::ostream& stream)
    : stream_(stream)
{ }

void Logger::print(const std::string& txt) const
{
    std::lock_guard streamLock(coutMtx_);
    stream_ << txt << std::endl;
}

Logger& operator<<(Logger& logger, const std::string& txt)
{
    logger.print(txt);

    return logger;
}