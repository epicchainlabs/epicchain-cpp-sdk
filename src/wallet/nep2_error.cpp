#include "epicchaincpp/wallet/xep2_error.hpp"

namespace epicchaincpp {
namespace xep2_error {

XEP2Error invalidPassphrase(const std::string& message) {
    return XEP2Error("Invalid passphrase: " + message);
}

XEP2Error invalidFormat(const std::string& message) {
    return XEP2Error("Invalid format: " + message);
}

} // namespace xep2_error
} // namespace epicchaincpp