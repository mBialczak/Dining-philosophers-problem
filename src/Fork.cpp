#include "Fork.hpp"

// Fork::Fork(const std::shared_ptr<Logger>& logger)   // TODO: VERIFY
Fork::Fork(Logger& logger)
    : logger_(logger),
      currently_used(false)
{ }