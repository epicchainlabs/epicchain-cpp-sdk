#pragma once

#include "../epicchain_swift_error.hpp"

namespace epicchaincpp {

// Helper namespace for XEP2Error factory functions
namespace xep2_error {
    /**
     * Create an invalid passphrase error
     * @param message The error message
     * @return A XEP2Error with invalid passphrase message
     */
    XEP2Error invalidPassphrase(const std::string& message);

    /**
     * Create an invalid format error
     * @param message The error message
     * @return A XEP2Error with invalid format message
     */
    XEP2Error invalidFormat(const std::string& message);
}

} // namespace epicchaincpp