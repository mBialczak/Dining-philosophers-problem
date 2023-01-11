#include "Logger.hpp"

Logger::Logger(std::ostream& stream)
    : stream_(stream)
{ }

template <typename typeToPrint>
void Logger::print(const typeToPrint& elementToPrint) const
{
    std::lock_guard streamLock(coutMtx_);
    stream_ << elementToPrint << std::endl;
}

Logger& operator<<(Logger& logger, const std::string& txt)
{
    logger.print(txt);

    return logger;
}
