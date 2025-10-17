#include "epicchaincpp/logger.hpp"

namespace epicchaincpp {

// Initialize static members
LogLevel Logger::currentLevel_ = LogLevel::INFO;
std::mutex Logger::logMutex_;
bool Logger::colorEnabled_ = true;

} // namespace epicchaincpp