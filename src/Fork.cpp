#include "Fork.hpp"

Fork::Fork(Logger& logger)
    : logger_(logger),
      currently_used(false)
{ }